# first attempt to write a gan to run over Test Beam simulation

from numpy import expand_dims
from numpy import split
from numpy import squeeze
from numpy import zeros
from numpy import ones
from numpy import vstack
from numpy import array
from numpy.random import randn
from numpy.random import randint
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import Reshape
from tensorflow.keras.layers import Flatten
from tensorflow.keras.layers import Conv2D
from tensorflow.keras.layers import Conv2DTranspose
from tensorflow.keras.layers import LeakyReLU
from tensorflow.keras.layers import Dropout
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import h5py

# define the standalone discriminator model
def define_discriminator(in_shape=(100,80,1)):
    model = Sequential()
    model.add(Conv2D(64, (3,3), strides=(2, 2), padding='same', input_shape=in_shape))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.4))
    model.add(Conv2D(64, (3,3), strides=(2, 2), padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.4))
    model.add(Flatten())
    model.add(Dense(1, activation='sigmoid'))
    # compile model
    #opt = SGD(lr=0.0002, momentum=0.5)
    opt = Adam(lr=0.0002, beta_1=0.5)
    model.compile(loss='binary_crossentropy', optimizer=opt, metrics=['accuracy'])
    return model

# define the standalone generator model
def define_generator(latent_dim):
    model = Sequential()
    # foundation for 25x20 image
    # 128 is the number of images which can be generated, in the convolutional layer
    n_nodes = 128 * 25 * 20
    model.add(Dense(n_nodes, input_dim=latent_dim))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Reshape((25, 20, 128)))
    # upsample to 50x40
    model.add(Conv2DTranspose(128, (4,4), strides=(2,2), padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    # upsample to 100x80
    model.add(Conv2DTranspose(128, (4,4), strides=(2,2), padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    # create single output feature map (the actual generated image)
    # preserve dimensions so use a kernel which is a multiple
    model.add(Conv2D(1, (25,20), activation='tanh', padding='same'))
    return model

# define the combined generator and discriminator model, for updating the generator
def define_gan(g_model, d_model):
    # make weights in the discriminator not trainable
    d_model.trainable = False
    # connect them
    model = Sequential()
    # add generator
    model.add(g_model)
    # add the discriminator
    model.add(d_model)
    # compile model
    #opt = SGD(lr=0.0002, momentum=0.5)
    opt = Adam(lr=0.0002, beta_1=0.5)
    model.compile(loss='binary_crossentropy', optimizer=opt)
    return model

# load cvn maps
def load_real_samples():
    inFile = h5py.File('h5_train/gan_reco_20000_TrainData.h5caf.h5', 'r')
    pm = array(inFile['cvnmap'])
    pm_shape = pm.reshape(pm.shape[0], 2, 100, 80)
    pm_xz, pm_yz = (expand_dims(squeeze(split(pm_shape, 2, axis=1)), axis=-1).astype('float32') - 127.5) / 127.5
    return pm_xz

# select real samples
def generate_real_samples(dataset, n_samples):
    # choose random instances
    ix = randint(0, dataset.shape[0], n_samples)
    # retrieve selected images
    X = dataset[ix]
    # generate 'real' class labels (1)
    y = ones((n_samples, 1))
    return X, y

# generate points in latent space as input for the generator
def generate_latent_points(latent_dim, n_samples):
    # generate points in the latent space
    x_input = randn(latent_dim * n_samples)
    # reshape into a batch of inputs for the network
    x_input = x_input.reshape(n_samples, latent_dim)
    return x_input

# use the generator to generate n fake examples, with class labels
def generate_fake_samples(g_model, latent_dim, n_samples):
    # generate points in latent space
    x_input = generate_latent_points(latent_dim, n_samples)
    # predict outputs
    X = g_model.predict(x_input, verbose=0)
    # create 'fake' class labels (0)
    y = zeros((n_samples, 1))
    return X, y

# create and save a plot of generated images (reversed grayscale)
def save_plot(examples_fake, examples_real, epoch, n=10):
    # plot images
    for i in range(n * n):
        # define subplot
        plt.subplot(n, n, 1 + i)
        # turn off axis
        #plt.axis('off')
        # plot raw pixel data
        plt.imshow(examples_fake[i, :, :, 0], cmap='gray_r')
    # save plot to file
    filename = 'generated_plot_e%03d.png' % (epoch+1)
    plt.savefig(filename)
    plt.clf()
    for i in range(n * n):
        # define subplot
        plt.subplot(n, n, 1 + i)
        # turn off axis
        #plt.axis('off')
        # plot raw pixel data
        plt.imshow(examples_real[i, :, :, 0], cmap='gray_r')
    # save plot to file
    filename = 'trainexamples_plot_e%03d.png' % (epoch+1)
    plt.savefig(filename)

# evaluate the discriminator, plot generated images, save generator model
def summarize_performance(epoch, g_model, d_model, dataset, latent_dim, n_samples=100):
    # prepare real samples
    X_real, y_real = generate_real_samples(dataset, n_samples)
    # evaluate discriminator on real examples
    _, acc_real = d_model.evaluate(X_real, y_real, verbose=0)
    # prepare fake examples
    x_fake, y_fake = generate_fake_samples(g_model, latent_dim, n_samples)
    # evaluate discriminator on fake examples
    _, acc_fake = d_model.evaluate(x_fake, y_fake, verbose=0)
    # summarize discriminator performance
    print('>Accuracy real: %.0f%%, fake: %.0f%%' % (acc_real*100, acc_fake*100))
    # save plot
    save_plot(x_fake, X_real, epoch)
    # save the generator model tile file
    filename = 'generator_model_%03d.h5' % (epoch + 1)
    g_model.save(filename)

# create a line plot of loss for the gan and save to file
def plot_history(d_loss_real_history, d_acc_real_history,
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
    plt.savefig('loss_acc.png')
    plt.close()

# train the generator and discriminator
def train(g_model, d_model, gan_model, dataset, latent_dim, n_epochs=100, n_batch=250):
    bat_per_epo = int(dataset.shape[0] / n_batch)
    half_batch = int(n_batch / 2)
    d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history = list(), list(), list(), list(), list()
    # manually enumerate epochs
    for i in range(n_epochs):
        # enumerate batches over the training set
        for j in range(bat_per_epo):
            # get randomly selected 'real' samples
            X_real, y_real = generate_real_samples(dataset, half_batch)
            # update discriminator model weights 
            d_loss_real, d_acc_real = d_model.train_on_batch(X_real, y_real)
            # generate 'fake' examples
            X_fake, y_fake = generate_fake_samples(g_model, latent_dim, half_batch)
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
        if (i+1) % 1 == 0:
            summarize_performance(i, g_model, d_model, dataset, latent_dim)
        plot_history(d_loss_real_history, d_acc_real_history, d_loss_fake_history, d_acc_fake_history, g_loss_history)

# size of the latent space
latent_dim = 100
# create the discriminator
d_model = define_discriminator()
print("Discriminator model:")
d_model.summary()
# create the generator
g_model = define_generator(latent_dim)
print("Generator model:")
g_model.summary()
# create the gan
gan_model = define_gan(g_model, d_model)
print("GAN model:")
gan_model.summary()
# load image data
dataset = load_real_samples()
# train model
train(g_model, d_model, gan_model, dataset, latent_dim, 10)
