import configargparse

def parse():
    parser = configargparse.ArgumentParser(description='GAN training')

    # See the example config for a description of each of these
    parser.add_argument('-c', required=True, is_config_file=True)
    parser.add_argument('--name')

    parser.add_argument('--model_file', default=None)
    
    parser.add_argument('--batch_size', type=int)
    parser.add_argument('--test_size', type=float)
    
    parser.add_argument('--train_iterations', type=int)
    parser.add_argument('--eval_iterations', type=int)
    
    parser.add_argument('--dataset')
    
    parser.add_argument('--learning_rate', type=float)
    parser.add_argument('--momentum', type=float)
    parser.add_argument('--nesterov', action='store_true')
    
    parser.add_argument('--epochs', type=int)
    parser.add_argument('--learning_rate_factor', type=float)
    parser.add_argument('--learning_rate_patience', type=int)
    parser.add_argument('--early_stopping_patience', type=int)
    
    parser.add_argument('--out_directory')

    config = parser.parse_args()
    parser.print_values()

    return config
