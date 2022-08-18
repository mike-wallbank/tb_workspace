import os
import sys

import random

from PandAna import *

# Vars to save to the output h5
def kPDG(tables):
    return tables['rec.mc.nu']['pdg']
kPDG = Var(kPDG)

def kMap(tables):
    return tables['rec.training.cvnmaps']['cvnmap']

if __name__ == '__main__':

    indir = sys.argv[1]
    outdir = sys.argv[2]
    print('Change files in '+indir+' to training files in '+outdir)
    files = [f for f in os.listdir(indir) if 'h5caf.h5' in f]
    files = random.sample(files, len(files))
    print('There are '+str(len(files))+' files.')

    # One file at a time to avoid problems with loading a bunch of pixel maps in memory
    for i,f in enumerate(files):

        # Definte the output name and don't recreate it 
        outname = '{0}_TrainData{1}'.format(f[:-9], f[-9:])
        if os.path.exists(os.path.join(outdir,outname)):
            continue

        # Make a loader and the spectra to fill
        tables = loader([os.path.join(indir,f)])

        # Make 'spectra' (I think this is actually a dataframe?)
        dfPDG = spectrum(tables, kCut, kPDG)

        # GO GO GO
        tables.Go()

        # Don't save an empty file 
        if dfPDG.entries() == 0:
            print(str(i)+': File '+f+' is empty.')
            continue

        # # Concat the dataframes to line up label and map
        # # join='inner' ensures there is both a label and a map for the slice 
        # df = pd.concat([specLab.df(), specMap.df(), specSign.df(), specEnergy.df()], axis=1, join='inner').reset_index()

        # # Save in an h5
        # hf = h5py.File(os.path.join(outdir,outname),'w')
        # hf.create_dataset('run',       data=df['run'],         compression='gzip')
        # hf.create_dataset('subrun',    data=df['subrun'],      compression='gzip')
        # hf.create_dataset('cycle',     data=df['cycle'],       compression='gzip')
        # hf.create_dataset('event',     data=df['evt'],         compression='gzip')
        # hf.create_dataset('slice',     data=df['subevt'],      compression='gzip')
        # hf.create_dataset('label',     data=df['interaction'], compression='gzip')
        # hf.create_dataset('PDG',       data=df['pdg'],         compression='gzip')
        # hf.create_dataset('E',         data=df['nuenergy'],    compression='gzip')

        # hf.create_dataset('cvnmap',    data=np.stack(df['cvnmap']), compression='gzip')
        # hf.close()
