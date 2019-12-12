import subprocess
from time import time
import os, sys
import json
#TODO minimum 3 grafy z rozna trudnoscia
graph_paths = [
  "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2", "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2",
  "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2", "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2",
  "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2", "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2",
  "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2", "graph2",  "graph2", "graph2", "graph2", "graph2", "graph2"
]
nrs_of_iterations = [
  100
]
#TODO sprawdzic z automatycznie dobierana liczna threadsow
nrs_of_threads = [
  1
]

date_start = int(time())
# try:
#     os.stat(f"./results/{date_start}")
# except:
#     os.mkdir(f"./results/{date_start}") 
data = []
for graph_path in graph_paths: 
  for nr_of_iteration in nrs_of_iterations:
    for nr_of_threads in nrs_of_threads:
      bashCommand = f"./a.out 1 200 {nr_of_iteration} {nr_of_threads} ./graphs/{graph_path}"
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