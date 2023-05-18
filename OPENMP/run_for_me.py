import subprocess
import statistics
import csv

# Replace `mpi_code_file` with the path to your MPI code file
code_file = '/home/joao-oliveira/Documents/Repositories/UFJF/Parallel-Programming/OPENMP/my-test/trapezoidal_openmp.c'

# Replace `csv_file` with the path where you want to write the CSV file
csv_file = '/home/joao-oliveira/Documents/Repositories/UFJF/Parallel-Programming/OPENMP/my-test/trapezoidal_openmp.csv'

# List of process counts to run the code with
process_counts = [1, 2, 4]
##process_counts = [1, 2, 4]
# Number of times to run the code for each process count
n_runs = 30
compile_output = subprocess.check_output(['gcc', '-O3', '-lm', '-fopenmp', code_file, '-o', 'open_mp_code'])
row = []
row.append('Processes')
for i in range(1, n_runs+1):
    str_ = "Run "+str(i)
    row.append(str_)

row.append('Mean')
row.append('Stdev')

# Write the headers to the CSV file
with open(csv_file, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(row)

# Run the code for each process count
for np in process_counts:
    # List to store the run times
    run_times = []
    print("Running for n = {}".format(np))
    # Run the code n_runs times
    for i in range(n_runs):
        # print("\tp = {}".format(i))
        # Run the MPI code with mpiexec
        command = ['./open_mp_code', str(np)]
        output = subprocess.check_output(command)

        # Extract the run time from the output
        time = float(output.decode().strip())

        # Add the run time to the list
        run_times.append(time)

    # Calculate the mean and standard deviation of the run times
    mean = statistics.mean(run_times)
    stdev = statistics.stdev(run_times)

    # Write the run times, mean, and standard deviation to the CSV file
    with open(csv_file, 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([np] + run_times + [mean, stdev])
