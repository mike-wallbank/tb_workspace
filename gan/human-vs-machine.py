# Script to set up the ultimate show-down between human and mahchine
# (can humans distinguish between real or generator events?)

import numpy as np
import h5py
from tensorflow import keras
import sys
from matplotlib import pyplot as plt
import time

def show_real(events):
    # pick a random event
    event_number = np.random.randint(0, events.shape[0])
    # set up the image
    image = events[event_number].reshape(2, 100, 80)
    image_reduced = image[:,0:32,24:56]
    image_xz, image_yz = np.squeeze(np.split(image_reduced, 2))
    plt.imshow(image_xz.T, cmap='gray_r')
    plt.show(block=False)
    plt.pause(3)
    plt.close()

def show_fake(model, latent_dim):
    # generate points in the latent space 
    x_input = np.random.randn(latent_dim)
    x_input = x_input.reshape(1, latent_dim)
    X = np.squeeze(model.predict(x_input, verbose=0))
    plt.imshow(X.T, cmap='gray_r')
    plt.show(block=False)
    plt.pause(3)
    plt.close()

# Set up real data
real_file = h5py.File('gan_reco_20000_TrainData.h5caf.h5','r')
real_events = np.array(real_file['cvnmap'])

# Set up generator to generate some fake events
gen_model = keras.models.load_model('generator_model_1000.h5')

print("""

Welcome to the ultimate battle of human-vs-machine.
Humanity has been waiting to distiguish between real and fake images of events from NOvA Test Beam!

""")

number_of_goes = int(sys.argv[1]) if len(sys.argv) > 1 else 100
print("Showing you {} images of events...".format(number_of_goes))

n_real = [0,0]
n_fake = [0,0]

for go in range(number_of_goes):

    # randomly pick real (0) or fake (1)
    real_or_fake = np.random.randint(0, 2)

    # show the image
    if real_or_fake == 0: show_real(real_events)
    else: show_fake(gen_model, 100)

    # ask for guess
    guess = ''
    while guess not in ['real', 'fake']:
        guess = input("Guess 'real' or fake': ")

    if real_or_fake == 0:
        if guess == 'real':
            print("Yep, that was real!"); n_real[0] += 1
        else:
            print("Nope, that was real!"); n_real[1] += 1
    else:
        if guess == 'fake':
            print("Yep, that was fake!"); n_fake[0] += 1
        else:
            print("Nope, that was fake!"); n_fake[1] += 1

    time.sleep(1)
        
print("""

You correctly guessed {} out of {} real images ({}%), and thought {} were fake ({}%).
You correctly guessed {} out of {} fake images ({}%), and thought {} were real ({}%).

""".format(n_real[0], sum(n_real), n_real[0]*100./sum(n_real), n_real[1], n_real[1]*100./sum(n_real),
           n_fake[0], sum(n_fake), n_fake[0]*100./sum(n_fake), n_fake[1], n_fake[1]*100./sum(n_fake)))
