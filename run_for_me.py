import subprocess
import statistics
import csv
import multiprocessing

# Replace `mpi_code_file` with the path to your MPI code file
mpi_code_file = '/path/to/mpi_code.c'

# Replace `csv_file` with the path where you want to write the CSV file
csv_file = '/path/to/output.csv'

# Get the number of available CPU cores
num_cores = multiprocessing.cpu_count()
print(f"Number of CPU cores: {num_cores}")

# Number of times to run the code for each process count
n_runs = 3

# Write the headers to the CSV file
with open(csv_file, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Processes', 'Run 1', 'Run 2', 'Run 3', 'Mean', 'Stdev'])

# Run the code for each process count
for np in num_cores:

    # List to store the run times
    run_times = []

    # Run the code n_runs times
    for i in range(n_runs):
        # Run the MPI code with mpiexec
        command = ['mpiexec', '-n', str(np), 'mpi_code']
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
