import os
import multiprocessing
import re
import numpy as np

from tensorflow import keras
from tensorflow.keras.optimizers import SGD
from keras import backend as K
from tensorflow.python.framework import graph_util
import tensorflow as tf

import utils.architecture as ac
import utils.generator as gen

class model():
    def __init__(self, config):
        self._config = config
        self.latent_dim = 100
        self.generator_model = ac.generator(self.latent_dim)
        self.discriminator_model = ac.discriminator()
        self.gan_model = ac.gan(self.generator_model, self.discriminator_model)
        self.epoch = 0

    # Setup the data generators and compile the model then fit
    def train(self, train_data, eval_data):
        
