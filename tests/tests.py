import subprocess
import random
import math
import os
import random
import csv
from decimal import Decimal, ROUND_HALF_UP


def run_program(args):
    # Get the directory in which the script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Construct the path to the runme executable
    runme_path = os.path.join(script_dir, '..', 'runme')

    # Execute the command
    process = subprocess.Popen(f"{runme_path} {args}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    process.wait()

    if process.returncode == 0:
        result_file_path = os.path.join(script_dir, '..', 'result.txt')
        # Read the results from result.txt
        with open(result_file_path, 'r') as file:
            results = file.read()
    else:
        results = ''
    
    return process.returncode, results, stderr.decode().strip()

def round_sf(num, n_sig_fig):
    if num != 0:
        return round(Decimal(num), -Decimal(num).adjusted() + (n_sig_fig - 1))
    return 0  # Handle the case where the number is 0

def calculate_norm(vector):
    """ Calculate the Euclidean norm of a vector. """
    return math.sqrt(sum([x**2 for x in vector]))

def generate_test_case(n,max_dimension=10):
    #n = random.randint(1, max_dimension)
    lattice = []
    norms = []

    for i in range(n):
        row = [random.randint(-10, 10) for i in range(n)]
        lattice.append(f"[{' '.join(map(str, row))}]")
        norms.append(calculate_norm(row))

    return ' '.join(lattice), norms

def permute_lattice(lattice):
    vectors = lattice.strip().split('] [')

    if vectors[0].startswith('['):
        vectors[0] = vectors[0][1:]
    if vectors[-1].endswith(']'):
        vectors[-1] = vectors[-1][:-1]

    # Shuffle the list of vectors
    random.shuffle(vectors)

    # Join the vectors back into a string, adding back the brackets
    return ' '.join(f'[{vector}]' for vector in vectors)


def uniform_scale(lattice, scale_factor=None):
    """
    Uniformly scale all vectors in the lattice by a random scale factor.
    """
    vectors = lattice.strip().split('] [')

    if vectors[0].startswith('['):
        vectors[0] = vectors[0][1:]
    if vectors[-1].endswith(']'):
        vectors[-1] = vectors[-1][:-1]

    # Generate a random scale factor if not provided
    if scale_factor is None:
        scale_factor = random.uniform(0.5, 2)  # for example, between 0.5 and 2

    # Scale each vector
    scaled_vectors = []
    for vector in vectors:
        # Split the vector into numbers, scale them, and reassemble the vector
        numbers = [str(int(num) * scale_factor) for num in vector.split()]
        scaled_vector = f"[{' '.join(numbers)}]"
        scaled_vectors.append(scaled_vector)

    return ' '.join(scaled_vectors), scale_factor

def run_prop_tests(test_case, result,norms):

    assert result > 0, f"Positivity test failed for case: {test_case}"

    assert result <= min(norms), f"Min norm test failed for case: {test_case}"

    perm_result = float(run_program(permute_lattice(test_case))[1])
    assert result == perm_result, f"Permutation test failed for case: {test_case}"

    scaled_basis, scale_factor = uniform_scale(test_case)
    scaled_result = float(run_program(scaled_basis)[1])
    assert round_sf(result * scale_factor,10) == round_sf(scaled_result,10), f"Scale test failed for case: {test_case}"

    return True



def run_regression_tests(csv_file):
    
    invalid_inputs = ['','1','[1', '1]', '[1 0][1]', '[word]', '[1,0] [0,1]', "[1 0][0 1]", "[[1 0] [0 1]], [[1 0], [0 1]]"]
    invalid_inputs_message = "Error: Invalid argument."
    non_basis = [

    "[0]",  # 1x1 matrix

    "[1 0] "
    "[0 0]",  # 2x2 matrix

    "[1 0 0] "
    "[0 1 0] "
    "[1 1 0]",  # 3x3 matrix

    "[1 0 0 0] "
    "[0 1 0 0] "
    "[0 0 1 0] "
    "[1 1 1 0]",  # 4x4 matrix

    "[1 0 0 0 0] "
    "[0 1 0 0 0] "
    "[0 0 1 0 0] "
    "[0 0 0 1 0] "
    "[1 1 1 1 0]",  # 5x5 matrix

    "[1 0 0 0 0 0] "
    "[0 1 0 0 0 0] "
    "[0 0 1 0 0 0] "
    "[0 0 0 1 0 0] "
    "[0 0 0 0 1 0] "
    "[1 1 1 1 1 0]",  # 6x6 matrix

    "[1 0 0 0 0 0 0] "
    "[0 1 0 0 0 0 0] "
    "[0 0 1 0 0 0 0] "
    "[0 0 0 1 0 0 0] "
    "[0 0 0 0 1 0 0] "
    "[0 0 0 0 0 1 0] "
    "[1 1 1 1 1 1 0]",  # 7x7 matrix

    "[1 0 0 0 0 0 0 0] "
    "[0 1 0 0 0 0 0 0] "
    "[0 0 1 0 0 0 0 0] "
    "[0 0 0 1 0 0 0 0] "
    "[0 0 0 0 1 0 0 0] "
    "[0 0 0 0 0 1 0 0] "
    "[0 0 0 0 0 0 1 0] "
    "[1 1 1 1 1 1 1 0]",  # 8x8 matrix

    "[1 0 0 0 0 0 0 0 0] "
    "[0 1 0 0 0 0 0 0 0] "
    "[0 0 1 0 0 0 0 0 0] "
    "[0 0 0 1 0 0 0 0 0] "
    "[0 0 0 0 1 0 0 0 0] "
    "[0 0 0 0 0 1 0 0 0] "
    "[0 0 0 0 0 0 1 0 0] "
    "[0 0 0 0 0 0 0 1 0] "
    "[1 1 1 1 1 1 1 1 0]",  # 9x9 matrix

    "[1 0 0 0 0 0 0 0 0 0] "
    "[0 1 0 0 0 0 0 0 0 0] "
    "[0 0 1 0 0 0 0 0 0 0] "
    "[0 0 0 1 0 0 0 0 0 0] "
    "[0 0 0 0 1 0 0 0 0 0] "
    "[0 0 0 0 0 1 0 0 0 0] "
    "[0 0 0 0 0 0 1 0 0 0] "
    "[0 0 0 0 0 0 0 1 0 0] "
    "[0 0 0 0 0 0 0 0 1 0] "
    "[1 1 1 1 1 1 1 1 1 0] " # 10x10 matrix
    ]

    non_basis_message = "Error: Provided vectors are not linearly independent."
    for case in invalid_inputs:
        return_code, result, error_message = run_program(case)
        assert return_code == 1, f"Return code: {return_code}, Expected: 1"
        assert error_message == invalid_inputs_message, f"Error message: {error_message}, Expected: {invalid_inputs_message}"        
        print(f"Regression test passed for invalid input: {case}")
    k=1
    for case in non_basis:
        return_code, result, error_message = run_program(case)
        assert return_code == 1, f"Return code: {return_code}, Expected: 1"
        assert error_message == non_basis_message, f"Error message: {error_message}, Expected: {non_basis_message}"        
        print(f"Regression test passed for invalid basis: dim {k}")
        k +=1

    with open(csv_file, mode='r') as file:
        reader = csv.reader(file)
        next(reader)

        for row in reader:
            dimension, bit, type, test_case, expected_result = row
            return_code, result, error_message = run_program(test_case)
            result, expected_result = float(result), float(expected_result)
            result, expected_result = round_sf(result,10), round_sf(expected_result,10)
            assert result == expected_result, f"Regression test failed for case: {test_case}"
            print(f"Regression test passed for, Dimension: {dimension}. Type: {type}. Bit: {bit}.")

def main():
    try:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        csv_file = os.path.join(script_dir, 'test_cases.csv')

        run_regression_tests(csv_file)

        i = 0
        while i < 10:
            test_case, norms = generate_test_case(i+1)
            return_code, result, error_message = run_program(test_case)

            if return_code != 0:
                continue
            else:
                i+=1
                result = float(result)
                if run_prop_tests(test_case, result, norms):
                    print(f"Property tests passed for case: random lattice {i}.")

    except AssertionError as e:
        print("Test failed:", e)


if __name__ == "__main__":
    main()

