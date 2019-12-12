import json
import argparse as arg
parser = arg.ArgumentParser("Aggregate & make plots with data from mobile robot paralelism")
parser.add_argument('target_path', type=str, help="path to JSON file with parallelism results")
# parser.add_argument('ground_truth_file_path', type=str, help="path to SEQ file with ground truth values")
# parser.add_argument('-g', '--gesture_name', metavar='NAME', type=str, default=None, help="name of gesture to be parsed, optional")
args = parser.parse_args()
target_path = args.target_path

with open(target_path) as json_file:
    list_pydb = json.load(json_file)

