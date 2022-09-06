import keras
import numpy as np

from tensorflow import keras

class data_generator(keras.utils.Sequence):

    def __init__(self, dataset, batch_size):
        self._batchsize = batch_size
        self._dataset = dataset
        self.ids = dataset.ids

    # Length of an epoch (number of batches in epoch)
    def __len__(self):
        return self.ids.shape[0]//self._batchsize

    # Shuffle ids at the end of each epoch
    def on_epoch_end(self):
        np.random.shuffle(self.ids)

    # Return an entire batch
    def __getitem__(self, index):
        idx = self.ids[index*self._batchsize : (index+1)*self._batchsize]

        pms = []
        labels = []

        for i in idx:
            pm = np.array(self._dataset.load_pm(i))
            label = self._dataset.load_label(i)

            # reshape the data and scale pixels to be in [-0.5, 0.5]
            pm_shape = pm.reshape(2, 100, 80)
            pm_shape = pm_shape[:,0:32,24:56]
            pm_xz, pm_yz = (np.expand_dims(np.squeeze(np.split(pm_shape, 2, axis=0)), axis=-1).astype('float32') - 127.5) / 127.5

            pms.append(pm_xz)
            labels.append(label)

        return np.array(pms), np.array(labels)
