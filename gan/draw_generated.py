# wrapper around drawing function to generate and draw some examples from a model

import sys
from numpy.random import randn
from tensorflow.keras.models import load_model
from draw_pixelmaps import draw_map

# generate points in latent space as input for the generator
def generate_latent_points(latent_dim, n_samples):
    # generate points in the latent space
    x_input = randn(latent_dim * n_samples)
    # reshape into a batch of inputs for the network
    x_input = x_input.reshape(n_samples, latent_dim)
    return x_input

# use the generator to generate n fake examples, with class labels
def generate_fake_samples(model, latent_dim, n_samples):
    # generate points in latent space
    x_input = generate_latent_points(latent_dim, n_samples)
    # predict outputs
    X = model.predict(x_input, verbose=0)
    return X

if len(sys.argv) != 2:
    print("Usage: python draw_generated.py <model file>")
    exit()

model = load_model(sys.argv[1])
generated = generate_fake_samples(model, 100, 10)

draw_map(generated, "generated_examples")
