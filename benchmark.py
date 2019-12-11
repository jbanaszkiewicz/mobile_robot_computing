import subprocess
#TODO minimum 3 grafy z rozna trudnoscia
graph_paths = [
  "./graphs/graph2"
]
nrs_of_iterations = [
  100,
  300,
  500
]
#TODO sprawdzic z automatycznie dobierana liczna threadsow
nrs_of_threads = [
  1,
  4,
  8
]


for graph_path in graph_paths:
  for nr_of_iteration in nrs_of_iterations:
    for nr_of_threads in nrs_of_threads:
      bashCommand = f"./a.out 1 200 {nr_of_iteration} {nr_of_threads} {graph_path}"
      process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
      output, error = process.communicate()
      # print(str(output),error)
      duration, cost_best_path, _ =  output.decode("utf-8").split('\n')
      print(duration, cost_best_path)