import keras
import numpy as np

from tensorflow import keras

# A Sequence is a keras extension to generators that is threadsafe
class data_generator(keras.utils.Sequence):
    def __init__(self, dataset, batch_size):
        self._batchsize = batch_size
        self._dataset = dataset
        self.ids = dataset.ids

    # This is required to define the sequence
    def __len__(self):
        return self.ids.shape[0]//self._batchsize

    # shuffle ids at the end of each epoch
    def on_epoch_end(self):
        np.random.shuffle(self.ids)

    # getitem should return an entire batch
    def __getitem__(self, index):
        idx = self.ids[index*self._batchsize : (index+1)*self._batchsize]

        pms = []
        lab = []

        for i in idx:
            pm = self._dataset.load_pm(i)

            pms.append(pm)
            lab.append(self._dataset.load_label(i))

        return np.array(pms), np.array(lab)
