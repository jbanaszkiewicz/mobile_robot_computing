import subprocess

graph_paths = [
  "./graphs/graph1"
]
nrs_of_iterations = [
  500
]
nrs_of_threads = [
  1,
  4,
  8
]


for graph_path in graph_paths:
  for nr_of_iteration in nrs_of_iterations:
    for nr_of_threads in nrs_of_threads:
      bashCommand = f"./main 100 100 {nr_of_iteration} 0.2 {graph_path} {nr_of_threads}"
      process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
      output, error = process.communicate()
      # print(str(output),error)
      duration, cost_best_path, _ =  output.decode("utf-8").split('\n')
      print(duration, cost_best_path)