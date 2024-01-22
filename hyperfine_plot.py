import subprocess
import time
import random
import math
import os
import random
import csv
from decimal import Decimal, ROUND_HALF_UP
import json

def run_program(args):
    # Get the directory in which the script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Construct the path to the runme executable
    runme_path = os.path.join(script_dir, '..', 'runme')

    # Execute the command
    process = subprocess.Popen(f"{runme_path} {args}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    return process.returncode, stdout.decode().strip(), stderr.decode().strip()

def round_sf(num, n_sig_fig):
    if num != 0:
        return round(Decimal(num), -Decimal(num).adjusted() + (n_sig_fig - 1))
    return 0  # Handle the case where the number is 0

def calculate_norm(vector):
    """ Calculate the Euclidean norm of a vector. """
    return math.sqrt(sum([x**2 for x in vector]))

def generate_test_case(max_dimension=10):
    n = random.randint(1, max_dimension)
    lattice = []
    norms = []

    for i in range(n):
        row = [random.randint(-10, 10) for i in range(n)]
        lattice.append(f"[{' '.join(map(str, row))}]")
        norms.append(calculate_norm(row))

    return ' '.join(lattice), norms

def run_hyperfine(test_case):
    command = f"hyperfine --export-json - './runme {test_case}'"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    output = result.stdout

    # Parse the JSON output to extract the timing information
    data = json.loads(output)
    times = [bench['mean'] for bench in data['results']]
    return np.mean(times), np.std(times)

def plot_results(dimensions, times, std_devs):
    plt.errorbar(dimensions, times, yerr=std_devs, fmt='o', ecolor='red', capsize=5, label='Average time ± Std Dev')
    plt.xlabel('Dimension')
    plt.ylabel('Time (seconds)')
    plt.title('Hyperfine Execution Times by Lattice Dimension')
    plt.legend()
    plt.show()

def main():
    dimensions = []
    avg_times = []
    std_devs = []

    for i in range(1, 11):  # Example: for dimensions 1 to 10
        test_case, _ = generate_test_case(max_dimension=i)
        avg_time, std_dev = run_hyperfine(test_case)
        dimensions.append(i)
        avg_times.append(avg_time)
        std_devs.append(std_dev)

    plot_results(dimensions, avg_times, std_devs)

if __name__ == "__main__":
    main()
