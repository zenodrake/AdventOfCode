from os import path
from sys import argv




def get_input_file(test=0):
    '''generate the path to an input file for Advent of Code.
    This function relies on the input file being in the Inputs
    directory of the file being run. Further, the name of the input file
    should be named the same as the file being run
    '''

    if test:
        folder = path.dirname(argv[0])
        return path.join(folder, 'Inputs', 'test_day')
    else:
        file_name = path.basename(argv[0])
        folder = path.dirname(argv[0])
        
        return path.join(folder, 'Inputs', file_name[:file_name.index('.')])



def file_to_list(file_name):
    with open(file_name) as f:
        r = [line for line in f]

    return r
    
