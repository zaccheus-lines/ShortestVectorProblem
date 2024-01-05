#!/bin/bash

# Directory containing the files
directory="gen"

# Check if the directory exists and has .svp files
if [ -d "$directory" ] && [ "$(ls -A $directory/*.svp 2>/dev/null)" ]; then
    # Loop through each .svp file in the directory
    for svp_file in "$directory"/*.svp; do
        echo "Processing file: $svp_file"

        # Extract the base name and generate the corresponding .svs filename
        base_name=${svp_file%.*}
        svs_file="${base_name}".svs


        # Run the command and capture its output
        output=$(./runme $(cat $svp_file))
        echo "$output"

        # Read the expected output from the .svs file
        expected_output=$(cat $svs_file)
        echo "$expected_output"

        # Compare the outputs
        if [ "$output" == "$expected_output" ]; then
            echo "Output matches for $svp_file"
        else
            echo "Output does not match for $svp_file"
            fi   
    done
else
    echo "No .svp files found in $directory."
fi
