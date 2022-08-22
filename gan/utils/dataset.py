import h5py
import numpy as np

from sklearn.model_selection import train_test_split

class dataset():
    def __init__(self, config, files=None, run_info=False):
        self._config = config
        self._props = []

        # Loop over each file and count the number of pixel maps present
        for f in files or [0]:
            if f == 0:
                break

            h5 = h5py.File(f,'r')
            labels = h5['pdg'][:]

            # Note: This is where you could apply generator level cuts

            # the run info can sometimes be memory consuming, only load if needed
            if run_info:
                runs    = h5['run'][:]
                subruns = h5['subrun'][:]
                cycs    = h5['cycle'][:]
                evts    = h5['event'][:]
                sls     = h5['slice'][:]
                # store the file location and index within file for each
                for n, (label,run,subrun,cyc,evt,sl) in enumerate(zip(labels, runs, subruns, cycs, evts, sls)):
                    self._props.append({'file': f, 'idx': n, 'label': label, 
                                        'run': run, 'subrun': subrun, 'cyc': cyc, 'evt': evt, 'sl': sl})
            else:
                for n, label in enumerate(labs):
                    self._props.append({'file': f, 'idx': n, 'label': label})
        
            h5.close()
        else:
            self.prepare()

    # add external data properties to this dataset
    def add_props(self, props):
        self._props += props
        self.prepare()

    # set the available ids and shuffle
    def prepare(self):
        n = len(self._props)
        self.ids = np.arange(n)
        print('Loaded '+str(n)+' events')
        np.random.shuffle(self.ids)

    # split into two datasets of size frac and 1-frac
    def split(self, frac = 0.1):
        print('Splitting into '+str(1-frac)+' train and '+str(frac)+' eval...')
        train,eval = train_test_split(self._props, test_size=frac)

        d1 = dataset(self._config)
        d1.add_props(train)

        d2 = dataset(self._config)
        d2.add_props(eval)
        
        return d1, d2

    # load a given data property
    def load_prop(self, i):
        return self._props[i]
    
    # load a pixel map from an hdf5
    def load_pm(self, i):
        prop = self.load_prop(i)
        f = h5py.File(prop['file'],'r')
        pm = f['cvnmap'][prop['idx']]
        f.close()
        return pm

    # load a label from an hdf5
    def load_label(self, i):
        label = self.load_prop(i)['label']
        
        return label > 0
