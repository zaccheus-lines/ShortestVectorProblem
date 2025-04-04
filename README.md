# Shortest Vector Problem Solver

This project provides a C++ implementation for finding the length (Euclidean norm) of the shortest non-zero vector in a lattice. It utilises the Lenstra–Lenstra–Lovász (LLL) lattice basis reduction algorithm followed by the Schnorr-Euchner enumeration strategy.

## Building

The project uses a `Makefile` for building. To compile the programme, navigate to the project's root directory in your terminal and run:

```bash
make
```

This will generate an executable file named `runme` in the root directory, which is required for the test suite.

## Usage

The programme takes the lattice basis vectors as command-line arguments. The components of the vectors must be provided sequentially, enclosed in square brackets `[]` for each vector.

**Format:**

```bash
./runme [v1_1] v1_2 ... [v1_n] [v2_1] v2_2 ... [v2_n] ... [vn_1] vn_2 ... [vn_n]
```

Where:
*   `./runme` is the compiled executable.
*   `[vi_1] vi_2 ... [vi_n]` represents the components of the i-th basis vector \( v_i \). The first component of each vector must start with `[` and the last component must end with `]`.

**Example (2D Lattice):**

Suppose the basis vectors are \( v_1 = (1, 1) \) and \( v_2 = (0, 2) \).

```bash
./runme [1] [1] [0] [2]
```

**Example (3D Lattice):**

Suppose the basis vectors are \( v_1 = (1, 2, 3) \), \( v_2 = (4, 5, 6) \), and \( v_3 = (7, 8, 9) \).

```bash
./runme [1] 2 [3] [4] 5 [6] [7] 8 [9]
```

**Note:** The number of components provided must be a perfect square (n*n), corresponding to `n` vectors of dimension `n`. The provided vectors must be linearly independent.

## Output

The programme calculates the Euclidean norm (length) of the shortest non-zero vector found in the lattice and writes this value to a file named `result.txt` in the same directory where the executable is run. The output is formatted to 16 decimal places.

## Testing

A comprehensive test suite is provided in the `tests/` directory, implemented in Python (`tests/tests.py`). It requires Python 3 and uses standard libraries.

**Running Tests:**

Ensure the C++ programme has been compiled using `make` (creating the `runme` executable in the root directory). Then, navigate to the root directory and run the test script:

```bash
python3 tests/tests.py
```

**Test Coverage:**

The test suite includes several categories of tests:

1.  **Invalid Argument Tests:** Checks if the programme correctly identifies and reports errors for various malformed command-line inputs (e.g., incorrect bracketing, non-numeric values, incorrect number of arguments).
2.  **Basis Validity Tests:** Verifies that the programme correctly detects and reports errors when the provided input vectors do not form a valid, linearly independent basis (including the zero vector case).
3.  **Regression Tests:** Compares the programme's output against a set of predefined test cases stored in `tests/test_cases.csv`. The calculated shortest vector length is compared against the expected value, checking for agreement up to 16 significant figures.
4.  **Property Tests:** These tests verify fundamental mathematical properties of the shortest vector problem and the LLL/enumeration algorithms:
    *   **Positivity:** Asserts that the calculated norm of the shortest non-zero vector is strictly positive.
    *   **Minimum Norm Bound:** Checks that the calculated shortest vector norm is less than or equal to the norm of any of the input basis vectors.
    *   **Permutation Invariance:** Verifies that the result remains the same if the order of the input basis vectors is changed.
    *   **Scaling Invariance:** Confirms that if the entire basis is scaled by a factor \( k \), the calculated shortest vector norm also scales by \( |k| \).

The script will print output indicating the status of each test (passed or failed).

## Dependencies

**Runtime:**
*   Standard C++ Library.

**Building:**
*   A C++ compiler supporting C++11 or later (e.g., g++).
*   `make`.

**Testing:**
*   Python 3. 
