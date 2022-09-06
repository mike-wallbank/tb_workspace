from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Reshape
from keras.layers import Flatten
from keras.layers import Conv2D
from keras.layers import Conv2DTranspose
from keras.layers import LeakyReLU
from keras.layers import Dropout
from keras.layers import BatchNormalization
from keras.initializers import RandomNormal

# define the standalone generator model
def generator(latent_dim, save_name=None):

    model = Sequential()
    init = RandomNormal(stddev=0.02)

    # foundation for 8x8 image
    # 128 is the number of images which can be generated, in the convolutional layer
    n_nodes = 128 * 8 * 8
    model.add(Dense(n_nodes, kernel_initializer=init, input_dim=latent_dim))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Reshape((8, 8, 128)))
    # upsample to 16x16
    model.add(Conv2DTranspose(128, (4,4), strides=(2,2), padding='same', kernel_initializer=init))
    model.add(BatchNormalization(momentum=0.8))
    model.add(LeakyReLU(alpha=0.2))
    # upsample to 32x32
    model.add(Conv2DTranspose(128, (4,4), strides=(2,2), padding='same', kernel_initializer=init))
    model.add(BatchNormalization(momentum=0.8))
    model.add(LeakyReLU(alpha=0.2))
    # create single output feature map (the actual generated image)
    # preserve dimensions so use a kernel which is a multiple
    model.add(Conv2D(1, (8,8), activation='tanh', padding='same', kernel_initializer=init))

    print("Generator model:")
    model.summary()
    if save_name:
        plot_model(model, to_file=save_name, show_shapes=True, show_layer_names=True)

    return model

# define the standalone discriminator model
def discriminator(in_shape=(32,32,1), save_file=None):

    model = Sequential()
    init = RandomNormal(stddev=0.02)

    model.add(Conv2D(64, (3,3), strides=(2, 2), padding='same', kernel_initializer=init, input_shape=in_shape))
    model.add(BatchNormalization(momentum=0.8))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.4))
    model.add(Conv2D(64, (3,3), strides=(2, 2), padding='same', kernel_initializer=init))
    model.add(BatchNormalization(momentum=0.8))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.4))
    model.add(Flatten())
    model.add(Dense(1, activation='sigmoid'))

    print("Discriminator model:")
    model.summary()
    if save_file:
        plot_model(model, to_file=save_file, show_shapes=True, show_layer_names=True)

    return model

def gan(g_model, d_model, save_file=None):

    # make weights in the discriminator not trainable
    d_model.trainable = False

    # connect them
    model = Sequential()

    # add generator
    model.add(g_model)

    # add the discriminator
    model.add(d_model)

    print("GAN model:")
    model.summary()
    if save_file:
        plot_model(model, to_file=save_file, show_shapes=True, show_layer_names=True)

    return model
