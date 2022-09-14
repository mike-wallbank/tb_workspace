import os

from utils.model import model
from utils.dataset import dataset
from utils.parser import parse

#################################################################################

# Setup this trial's config
config = parse()

# Generate a list of files to use for training
files = [os.path.join(config.dataset,f) for f in os.listdir(config.dataset)]
data = dataset(config, files, keep_in_memory=True, run_info=False)

# Initialize the model
model_ = model(config)

# Train the model
model_.train(data)
