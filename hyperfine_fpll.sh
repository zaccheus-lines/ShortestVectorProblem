#!/bin/bash

# Directory to store results
result_directory="hyperfine_results"

# Create the result directory if it doesn't exist
mkdir -p "$result_directory"

# Number of dimensions to test
num_dimensions=10  # Change this to the desired number of dimensions

# Number of random lattices per dimension
num_lattices_per_dimension=100

# Loop through each dimension
for ((dimension = 1; dimension <= num_dimensions; dimension++)); do
    echo "Testing dimension: $dimension"

    # Create a directory for the current dimension
    dimension_directory="$result_directory/dimension_$dimension"
    mkdir -p "$dimension_directory"

    # Run hyperfine for each random lattice
    for ((lattice_num = 1; lattice_num <= num_lattices_per_dimension; lattice_num++)); do
        echo "Running hyperfine for random lattice $lattice_num"
        
        # Generate a random lattice using fpll and redirect output to /dev/null
        fpll_output=$(fpll -n $dimension -r -s 1 -t 0 2>/dev/null)

        # Measure the execution time using hyperfine and store the result
        hyperfine_output=$(hyperfine --quiet --warmup 1 "$fpll_output")
        echo "$hyperfine_output" >> "$dimension_directory/lattice_$lattice_num.txt"
    done
done

# Calculate the average run time for each dimension
for ((dimension = 1; dimension <= num_dimensions; dimension++)); do
    dimension_directory="$result_directory/dimension_$dimension"
    
    # Calculate the average run time using awk and print the result
    average_run_time=$(awk '/Mean/{sum+=$3}END{print sum/NR}' "$dimension_directory"/*.txt)
    echo "Average run time for dimension $dimension: $average_run_time seconds"
done
