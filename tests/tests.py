import subprocess
import random
import math
import os
import csv
from decimal import Decimal, ROUND_HALF_UP

def run_program(args):
    """
    Executes a program with specified arguments and reads the result.

    Args:
    args (str): Arguments to pass to the program.

    Returns:
    tuple: Return code, result from 'result.txt', and standard error output.
    """
    script_dir = os.path.dirname(os.path.abspath(__file__))
    runme_path = os.path.join(script_dir, '..', 'runme')

    process = subprocess.Popen(f"{runme_path} {args}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    process.wait()

    results = ''
    if process.returncode == 0:
        result_file_path = os.path.join(script_dir, '..', 'result.txt')
        with open(result_file_path, 'r') as file:
            results = file.read()
    
    return process.returncode, results, stderr.decode().strip()

def round_sf(num, n_sig_fig):
    """
    Rounds a number to a specified number of significant figures.

    Args:
    num (float): Number to round.
    n_sig_fig (int): Number of significant figures.

    Returns:
    Decimal: Rounded number.
    """
    if num != 0:
        return round(Decimal(num), -Decimal(num).adjusted() + (n_sig_fig - 1))
    return 0  # Return 0 if the number is zero.

def calculate_norm(vector):
    """
    Calculate the Euclidean norm of a vector.

    Args:
    vector (list): Vector of numbers.

    Returns:
    float: Euclidean norm of the vector.
    """
    return math.sqrt(sum([x**2 for x in vector]))

def generate_test_case(n, max_dimension=10):
    """
    Generates a test case lattice with norms.

    Args:
    n (int): Number of dimensions for the lattice.
    max_dimension (int): Maximum dimension for the lattice.

    Returns:
    tuple: Lattice and its norms.
    """
    lattice = []
    norms = []

    for i in range(n):
        row = [random.randint(-10, 10) for _ in range(n)]
        lattice.append(f"[{' '.join(map(str, row))}]")
        norms.append(calculate_norm(row))

    return ' '.join(lattice), norms

def permute_lattice(lattice):
    """
    Randomly permutes the vectors in a lattice.

    Args:
    lattice (str): Lattice as a string.

    Returns:
    str: Permuted lattice.
    """
    vectors = lattice.strip().split('] [')

    if vectors[0].startswith('['):
        vectors[0] = vectors[0][1:]
    if vectors[-1].endswith(']'):
        vectors[-1] = vectors[-1][:-1]

    random.shuffle(vectors)

    return ' '.join(f'[{vector}]' for vector in vectors)

def uniform_scale(lattice, scale_factor=None):
    """
    Uniformly scales all vectors in a lattice by a specified factor.

    Args:
    lattice (str): Lattice as a string.
    scale_factor (float): Scale factor k.

    Returns:
    tuple: Scaled lattice and scale factor.
    """
    vectors = lattice.strip().split('] [')

    if vectors[0].startswith('['):
        vectors[0] = vectors[0][1:]
    if vectors[-1].endswith(']'):
        vectors[-1] = vectors[-1][:-1]

    if scale_factor is None:
        scale_factor = random.uniform(0.5, 2)

    scaled_vectors = []
    for vector in vectors:
        numbers = [str(int(num) * scale_factor) for num in vector.split()]
        scaled_vector = f"[{' '.join(numbers)}]"
        scaled_vectors.append(scaled_vector)

    return ' '.join(scaled_vectors), scale_factor

def run_prop_tests(test_case, result, norms):
    """
    Runs property tests on a given test case.

    Args:
    test_case (str): Test case as a string.
    result (float): Result to test.
    norms (list): Norms of the vectors in the test case.

    Returns:
    bool: True if all tests pass.
    """
    assert result > 0, f"Positivity test failed for case: {test_case}"
    assert result <= min(norms), f"Min norm test failed for case: {test_case}"

    perm_result = float(run_program(permute_lattice(test_case))[1])
    assert result == perm_result, f"Permutation test failed for case: {test_case}"

    scaled_basis, scale_factor = uniform_scale(test_case)
    scaled_result = float(run_program(scaled_basis)[1])
    assert round_sf(result * scale_factor, 10) == round_sf(scaled_result, 10), f"Scale test failed for case: {test_case}"

    return True

def run_regression_tests(csv_file):
    """
    Runs regression tests from a CSV file.

    Args:
    csv_file (str): Path to the CSV file with test cases.
    """
    # Test cases for invalid inputs and non-basis matrices
    invalid_inputs = ['', '1', '[1', '1]', '[1 0][1]', '[word]', '[1,0] [0,1]', "[1 0][0 1]", "[[1 0] [0 1]], [[1 0], [0 1]]"]
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
    # Test each invalid input
    for case in invalid_inputs:
        return_code, result, error_message = run_program(case)
        assert return_code == 1, f"Return code: {return_code}, Expected: 1"
        assert error_message == invalid_inputs_message, f"Error message: {error_message}, Expected: {invalid_inputs_message}"
        print(f"Regression test passed for invalid input: {case}")

    # Test each non-basis matrix
    for k, case in enumerate(non_basis, 1):
        return_code, result, error_message = run_program(case)
        assert return_code == 1, f"Return code: {return_code}, Expected: 1"
        assert error_message == non_basis_message, f"Error message: {error_message}, Expected: {non_basis_message}"
        print(f"Regression test passed for invalid basis: dim {k}")

    # Test cases from CSV file
    with open(csv_file, mode='r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip the header

        for row in reader:
            dimension, bit, type, test_case, expected_result = row
            return_code, result, error_message = run_program(test_case)
            result, expected_result = float(result), float(expected_result)
            result, expected_result = round_sf(result, 10), round_sf(expected_result, 10)
            assert result == expected_result, f"Regression test failed for case: {test_case}"
            print(f"Regression test passed for, Dimension: {dimension}. Type: {type}. Bit: {bit}.")

def main():
    """
    Main function to run tests.
    """
    try:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        csv_file = os.path.join(script_dir, 'test_cases.csv')

        run_regression_tests(csv_file)

        for i in range(10):
            test_case, norms = generate_test_case(i+1)
            return_code, result, error_message = run_program(test_case)

            if return_code == 0:
                result = float(result)
                if run_prop_tests(test_case, result, norms):
                    print(f"Property tests passed for case: random lattice {i + 1}.")
    except AssertionError as e:
        print("Test failed:", e)


if __name__ == "__main__":
    main()
