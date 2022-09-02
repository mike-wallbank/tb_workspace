
import utils.architecture as ac
import utils.generator as gen

class model():

    def __init__(self, config):
        self._config = config
        self.latent_dim = config.latent_dim
        self.generator_model = ac.generator(self.latent_dim)
        self.discriminator_model = ac.discriminator()
        self.gan_model = ac.gan(self.generator_model, self.discriminator_model)

        if self._config.model_file:
            self.load_weights(self._config.model_file)
        else:
            self.epoch = 0


    # generate points in latent space as input for the generator
    def generate_latent_points(n_samples):
        x_input = randn(self.latent_dim * n_samples)
        x_input = x_input.reshape(n_samples, self.latent_dim)
        return x_input


    # use the generator to generate n fake examples, with class labels
    def generate_fake_samples(n_samples):
        x_input = generate_latent_points(n_samples)
        X =self.generator_model.predict(x_input, verbose=0)
        return X


    # Load weights from a file
    def load_weights(self, path):
        print('Loading model weights from '+path+'...')
        self.keras_model.load_weights(path)
        m = re.search('(\d\d\d).h5', path)
        if m:
            self.epoch = int(m.group(1))
            print('Loaded weights at epoch '+str(self.epoch))
        else:
            self.epoch=0
            print('Epoch could not be determined. Ignoring...')


    # Train the generator and discriminator
    def train(self, dataset):

        data_gen = gen.data_generator(dataset, self._config.batch_size)

        #half_batch = int(n_batch / 2)
        d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history = list(), list(), list(), list(), list()

        # compile models
        # if I do it here, does it work?  Will probably remove those annoying warnings, thinking about it...
        #opt = SGD(lr=0.0002, momentum=0.5)
        opt = Adam(lr=self._config.learning_rate, beta_1=self._config.learning_beta)
        self.discriminator_model.compile(loss='binary_crossentropy', optimizer=opt, metrics=['accuracy'])
        self.gan_model.compile(loss='binary_crossentropy', optimizer=opt)

        workers = multiprocessing.gpu_count()
        print('Starting training on '+str(workers)+' GPUs.')

        # manually enumerate epochs
        for epoch in range(self._config.epochs):

            # enumerate batches over the training set
            for batch in range(bat_per_epo):

                # get 'real' samples
                X_real = data_gen.__getitem__(batch)
                print(X_real.shape)
                y_real = ones((X_real.shape[0], 1))

                # update discriminator model weights 
                d_loss_real, d_acc_real = d_model.train_on_batch(X_real, y_real)

                # generate 'fake' examples
                X_fake = generate_fake_samples(self._config.batch_size)
                y_fake = zeros((self._config.batch_size, 1))

                # update discriminator model weights
                d_loss_fake, d_acc_fake = d_model.train_on_batch(X_fake, y_fake)

                # prepare points in latent space as input for the generator
                X_gan = generate_latent_points(latent_dim, n_batch)

                # create inverted labels for the fake samples
                y_gan = ones((n_batch, 1))

                # update the generator via the discriminator's error
                g_loss = gan_model.train_on_batch(X_gan, y_gan)

                # summarize loss on this batch
                print('>%d, %d/%d, d_real=%.3f, d_fake=%.3f, g_loss=%.3f, a_real=%d, a_fake=%d' % \
                      (i+1, j+1, bat_per_epo, d_loss_real, d_loss_fake, g_loss, int(100*d_acc_real), int(100*d_acc_fake)))

                # save history
                d_loss_real_history.append(d_loss_real)
                d_acc_real_history.append(d_acc_real)
                d_loss_fake_history.append(d_loss_fake)
                d_acc_fake_history.append(d_acc_fake)
                g_loss_history.append(g_loss)

                # evaluate the model performance, sometimes
                if (epoch+1) % 100 == 0:
                    summarize_performance(epoch, g_model, d_model, dataset, latent_dim)

        plot_history(d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history)

        # self.keras_model.fit(x=train_gen,
        #                      steps_per_epoch=self._config.train_iterations,
        #                      validation_data=eval_gen,
        #                      validation_steps=self._config.eval_iterations,
        #                      epochs=self._config.epochs,
        #                      callbacks=callbacks,
        #                      verbose=1,
        #                      workers=workers,
        #                      max_queue_size=128,
        #                      use_multiprocessing=True,
        #                      initial_epoch=self.epoch)

    def generate(self):
        
        p = self.gan_model.predict(np.array([pm]))
        return p[0]

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


# # create and save a plot of generated images (reversed grayscale)
# def save_plot(examples_fake, examples_real, epoch, n=10):
#     # plot images
#     for i in range(n * n):
#         # define subplot
#         plt.subplot(n, n, 1 + i)
#         # turn off axis
#         #plt.axis('off')
#         # plot raw pixel data
#         plt.imshow(examples_fake[i, :, :, 0], cmap='gray_r')
#     # save plot to file
#     filename = 'logs/generated_plot_e%04d.png' % (epoch+1)
#     plt.savefig(filename)
#     plt.clf()
#     for i in range(n * n):
#         # define subplot
#         plt.subplot(n, n, 1 + i)
#         # turn off axis
#         #plt.axis('off')
#         # plot raw pixel data
#         plt.imshow(examples_real[i, :, :, 0], cmap='gray_r')
#     # save plot to file
#     filename = 'logs/trainexamples_plot_e%04d.png' % (epoch+1)
#     plt.savefig(filename)
#     plt.clf()

# # evaluate the discriminator, plot generated images, save generator model
# def summarize_performance(epoch, g_model, d_model, dataset, latent_dim, n_samples=100):
#     # prepare real samples
#     X_real, y_real = generate_real_samples(dataset, n_samples)
#     # evaluate discriminator on real examples
#     _, acc_real = d_model.evaluate(X_real, y_real, verbose=0)
#     # prepare fake examples
#     x_fake, y_fake = generate_fake_samples(g_model, latent_dim, n_samples)
#     # evaluate discriminator on fake examples
#     _, acc_fake = d_model.evaluate(x_fake, y_fake, verbose=0)
#     # summarize discriminator performance
#     print('>Accuracy real: %.0f%%, fake: %.0f%%' % (acc_real*100, acc_fake*100))
#     # save plot
#     save_plot(x_fake, X_real, epoch)
#     # save the generator model tile file
#     filename = 'logs/generator_model_%04d.h5' % (epoch + 1)
#     g_model.save(filename)

# # create a line plot of loss for the gan and save to file
# def plot_history(d_loss_real_history, d_acc_real_history,
#                  d_loss_fake_history, d_acc_fake_history,
#                  g_loss_history):
#     # plot loss 
#     plt.subplot(2, 1, 1)
#     plt.plot(d_loss_real_history, label='d-loss (real)')
#     plt.plot(d_loss_fake_history, label='d-loss (fake)')
#     plt.plot(g_loss_history, label='gen-loss')
#     plt.legend()
#     # plot discriminator accuracy
#     plt.subplot(2, 1, 2)
#     plt.plot(d_acc_real_history, label='d-acc (real)')
#     plt.plot(d_acc_fake_history, label='d-acc (fake)')
#     plt.legend()
#     # save plot to file
#     plt.savefig('logs/loss_acc.png')
#     plt.close()

