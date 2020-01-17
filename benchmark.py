import subprocess
from time import time
import os, sys
import json
from tqdm import tqdm

graph_paths = [
  "graph100"
]
nrs_of_iterations = [
  1000
]

# nrs_of_threads = [
#   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
#   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
#   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
#   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
#   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
# ]
nrs_of_threads = [
  1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 
  3, 3, 3, 3, 3,
  4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 
  6, 6, 6, 6, 6,
  7, 7, 7, 7, 7, 
  8, 8, 8, 8, 8
]


date_start = int(time())
# try:
#     os.stat(f"./results/{date_start}")
# except:
#     os.mkdir(f"./results/{date_start}") 
data = []
for graph_path in  tqdm(graph_paths, desc='graphs_progress'): 
  for nr_of_iteration in tqdm(nrs_of_iterations, desc='iterrs_progress'):
    for nr_of_threads in tqdm(nrs_of_threads, desc='threads_progress'):
      bashCommand = f" mpirun -np {nr_of_threads} ./a.out 1 200 {nr_of_iteration} ./graphs/{graph_path}"
      process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
      output, error = process.communicate()
      # print(str(output),error)
      duration, cost_best_path, _ =  output.decode("utf-8").split('\n')
      dataPathName = f"{graph_path}_iters{nr_of_iteration}_threads{nr_of_threads}"
      
      single_data = {"name":             dataPathName,
                    "graph":            graph_path,
                    "nr_of_iteration":  nr_of_iteration,
                    "nr_of_threads":    nr_of_threads,
                    "duration":         duration,
                    "cost_best_path":   cost_best_path
                    }
      data.append(single_data)
with open(f"./results/{date_start}.json", "w") as json_file:
  json.dump(data, json_file, indent=4)
  json_file.write("\n")