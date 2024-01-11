#!/bin/bash

# Directory containing the files
directory="gen"
failed_directory="failed"

# Create the failed directory if it does not exist
mkdir -p "$failed_directory"

# Initialize counters for passed and failed comparisons
passed_count=0
failed_count=0

# Function to compare two floating-point numbers with a relative tolerance
compare_floats() {
    local num1=$1
    local num2=$2
    local relative_tolerance="1e-6"

    # Use awk to compare the floats
    awk -v n1="$num1" -v n2="$num2" -v tol="$relative_tolerance" '
        function abs(x) { return x < 0 ? -x : x; }
        BEGIN {
            rel_tol = tol * abs(n1 > n2 ? n1 : n2);
            if (abs(n1 - n2) <= rel_tol) 
                exit 0; 
            else 
                exit 1;
        }
    '
}

# Check if the directory exists and has .svp files
if [ -d "$directory" ] && [ "$(ls -A $directory/*.svp 2>/dev/null)" ]; then
    # Loop through each .svp file in the directory
    for svp_file in "$directory"/*.svp; do
        echo "Processing file: $svp_file"

        # Check if the file is a 64-bit file and skip it if true
        if [[ $svp_file == *"_64_"* ]]; then
            echo "Skipping 64-bit file: $svp_file"
            continue
        fi

        # Extract the base name and generate the corresponding .svs filename
        base_name=${svp_file%.*}
        svs_file="${base_name}".svs

        # Run the command and capture its output
        output=$(./runme $(cat $svp_file))
        echo "$output"

        # Read the expected output from the .svs file
        expected_output=$(cat $svs_file)
        echo "$expected_output"

        # Compare the outputs using the compare_floats function
        if compare_floats "$output" "$expected_output"; then
            echo "Output matches for $svp_file within the tolerance."
            ((passed_count++))
        else
            echo "Output does not match for $svp_file."
            ((failed_count++))
            cp "$svp_file" "$failed_directory/"
            cp "$svs_file" "$failed_directory/"
        fi
    done

    # Display the counts
    echo "Passed: $passed_count"
    echo "Failed: $failed_count"
else
    echo "No .svp files found in $directory."
fi
