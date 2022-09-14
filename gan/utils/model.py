import utils.architecture as architecture
import utils.generator as generator

import numpy as np

from keras.optimizers import Adam

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

class model():

    def __init__(self, config):
        self._config = config
        self.latent_dim = config.latent_dim
        self.generator_model = architecture.generator(self.latent_dim)

        if self._config.model_file:
            self.load_weights(self._config.model_file)
        else:
            self.epoch = 0


    # Use the generator to generate fake examples
    def generate_fake_samples(self, n_samples):
        x_input = self.generate_latent_points(n_samples)
        X = self.generator_model.predict(x_input, verbose=0)
        return X


    # Generate points in latent space as input for the generator
    def generate_latent_points(self, n_samples):
        x_input = np.random.randn(self.latent_dim * n_samples)
        x_input = x_input.reshape(n_samples, self.latent_dim)
        return x_input


    # Load weights from a file
    def load_weights(self, path):
        print("Loading model weights from {}...".format(path))
        self.generator_model.load_weights(path)
        m = re.search('(\d\d\d).h5', path)
        if m:
            self.epoch = int(m.group(1))
            print("Loaded weights at epoch {}".format(self.epoch))
        else:
            self.epoch=0
            print("Epoch could not be determined. Ignoring...")


    # Create and save a plot of images (reversed grayscale)
    def save_event_images(self, examples, file_name, n=10):
        for i in range(n * n):
            plt.subplot(n, n, 1 + i)
            # plt.axis('off')
            plt.imshow(examples[i, :, :, 0], cmap='gray_r')
        filename = "{}/{}.png".format(self._config.out_directory, file_name)
        plt.savefig(filename)
        plt.clf()


    # Save the model
    # copied from Micah's example -- don't understand any of this! (yet)
    def save_model(self):
        K.set_learning_phase(0)
        model = self.keras_model

        num_output = 1

        pred_node_names = ['output_out']
        pred = [tf.identity(model.outputs[i], name = pred_node_names[i])
                for i in range(num_output)]

        sess = K.get_session()
        od_graph_def = graph_util.convert_variables_to_constants(sess,
                                                         sess.graph.as_graph_def(),
                                                         pred_node_names)

        frozen_graph_path = 'model_'+self._config.name+'.pb'
        with tf.gfile.GFile(frozen_graph_path, 'wb') as f:
            f.write(od_graph_def.SerializeToString())


    # Plot loss for the gan
    def save_training_history(self,
                              d_loss_real_history, d_acc_real_history,
                              d_loss_fake_history, d_acc_fake_history,
                              g_loss_history):
        # plot loss
        plt.subplot(2, 1, 1)
        plt.plot(d_loss_real_history, label='d-loss (real)')
        plt.plot(d_loss_fake_history, label='d-loss (fake)')
        plt.plot(g_loss_history, label='gen-loss')
        plt.legend()
        # plot discriminator accuracy
        plt.subplot(2, 1, 2)
        plt.plot(d_acc_real_history, label='d-acc (real)')
        plt.plot(d_acc_fake_history, label='d-acc (fake)')
        plt.legend()
        # save plot to file
        plt.savefig("{}/loss_acc.png".format(self._config.out_directory))
        plt.close()


    # Evaluate the discriminator, plot generated images, save generator model
    def summarize_performance(self, discriminator_model, epoch, data_gen, n_samples=100):

        # performance on real samples
        # we shuffle at the end of the epoch, so we can just get the first batch and get
        # random events each time
        X_real, _ = data_gen.__getitem__(0)
        y_real = np.ones((n_samples, 1))
        _, acc_real = discriminator_model.evaluate(X_real[:n_samples], y_real, verbose=0)
        self.save_event_images(X_real, "traindata_plot_e{:04}".format(epoch+1))

        # performance on fake samples
        X_fake = self.generate_fake_samples(n_samples)
        y_fake = np.zeros((n_samples, 1))
        _, acc_fake = discriminator_model.evaluate(X_fake, y_fake, verbose=0)
        self.save_event_images(X_fake, "gendata_plot_e{:04}".format(epoch+1))

        # summarize discriminator performance
        print(">Accuracy real: {:.2%}, fake: {:.2%}".format(acc_real, acc_fake))

        # save the generator model tile file
        self.generator_model.save("{}/generator_model_e{:04}.h5".format(self._config.out_directory, (epoch+1)))


    # Train the generator and discriminator
    def train(self, dataset):

        half_batch = int(self._config.batch_size / 2)
        data_gen = generator.data_generator(dataset, self._config.batch_size)

        d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history = list(), list(), list(), list(), list()

        # for training, we need a discriminator model to both distinguish 'real' and 'fake'
        # events and to update the generator weights via backpropagation in a combined model
        opt = Adam(lr=self._config.learning_rate, beta_1=self._config.learning_beta)
        discriminator_model = architecture.discriminator()
        discriminator_model.compile(loss='binary_crossentropy', optimizer=opt, metrics=['accuracy'])
        gan_model = architecture.gan(self.generator_model, discriminator_model)
        gan_model.compile(loss='binary_crossentropy', optimizer=opt)

        # manually enumerate epochs
        for epoch in range(self._config.epochs):

            # enumerate batches over the training set
            for batch in range(data_gen.__len__()):

                # get half a batch of 'real' samples
                X_real, _ = data_gen.__getitem__(batch)
                X_real = np.split(X_real, 2)
                y_real = np.ones((half_batch, 1))

                # update discriminator model weights 
                d_loss_real, d_acc_real = discriminator_model.train_on_batch(X_real[0], y_real)

                # generate half a batch of 'fake' examples
                X_fake = self.generate_fake_samples(half_batch)
                y_fake = np.zeros((half_batch, 1))

                # update discriminator model weights
                d_loss_fake, d_acc_fake = discriminator_model.train_on_batch(X_fake, y_fake)

                # prepare points in latent space as input for the generator
                X_gan = self.generate_latent_points(half_batch*2)
                y_gan = np.ones((half_batch*2, 1))

                # update the generator via the discriminator's error
                g_loss = gan_model.train_on_batch(X_gan, y_gan)

                # summarize loss on this batch
                print(">{}, {}/{}, d_real={:.3}, d_fake={:.3}, g_loss={:.3}, a_real={:.0%}, a_fake={:.0%}" \
                      .format(epoch+1, batch+1, data_gen.__len__(), d_loss_real, d_loss_fake, g_loss, d_acc_real, d_acc_fake))

                # save history
                d_loss_real_history.append(d_loss_real)
                d_acc_real_history.append(d_acc_real)
                d_loss_fake_history.append(d_loss_fake)
                d_acc_fake_history.append(d_acc_fake)
                g_loss_history.append(g_loss)

            data_gen.on_epoch_end()

            # evaluate the model performance, sometimes
            if (epoch+1) % 100 == 0:
                self.summarize_performance(discriminator_model, epoch, data_gen)

        self.save_training_history(d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history)
