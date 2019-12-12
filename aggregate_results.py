import json
import argparse as arg
import matplotlib.pyplot as plt
import statistics
# parser = arg.ArgumentParser("Aggregate & make plots with data from mobile robot paralelism")
# parser.add_argument('target_path', type=str, help="path to JSON file with parallelism results")
# parser.add_argument('ground_truth_file_path', type=str, help="path to SEQ file with ground truth values")
# parser.add_argument('-g', '--gesture_name', metavar='NAME', type=str, default=None, help="name of gesture to be parsed, optional")
# args = parser.parse_args()
# target_path = args.target_path
target_path = "./results/many"
list_files = [  '1576181776.json',
                '1576181780.json',
                '1576181779.json',
                '1576181772.json',
                '1576181782.json',
                '1576181777.json',
                '1576181775.json',
                '1576181771.json',
                '1576181770.json',
                '1576181774.json']
list_results = []
for i in list_files:
    with open(f"{target_path}/{i}") as json_file:
        result = json.load(json_file)
    list_results.append(result[0])

print(len(list_results))
#TODO zrobic dane gdzie beda powarzalne warunki z jednym rpocesorem i zobaczyc czy wychodza te same wyniki
durations = [float(d["duration"]) for d in list_results]
costs = [float(d["cost_best_path"]) for d in list_results]
mean_cost = statistics.mean(costs)
min_cost = min(costs)
max_cost = max(costs)
mean_duration = statistics.mean(durations)
min_duration = min(durations)
max_duration = max(durations)
print(min_cost, " ", mean_cost, " ", max_cost)
print(min_duration, " ", mean_duration, " ", max_duration)


