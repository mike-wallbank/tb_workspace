import h5py
import numpy as np

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
                for n, label in enumerate(labels):
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
