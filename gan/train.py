import os

from utils.model import model
from utils.dataset import dataset
from utils.parser import parse

#################################################################################

# Setup this trial's config
config = parse()

# Generate a list of files to use for training
files = [os.path.join(config.dataset,f) for f in os.listdir(config.dataset)]
data = dataset(config, files, run_info=False)
train, test = data.split()

# Initialize the model
kModel = model(config)

# # GO GO GO
# kModel.train(train, test)
