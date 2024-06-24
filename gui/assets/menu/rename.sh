#!/bin/bash

# Iterate over all PNG files in the current directory and rename them to a 3-digit padded number.
for file in *.png;
do
    base_name=$(basename "$file" .png)
    if [[ "$base_name" =~ ^[0-9]+$ ]]; then
        padded_number=$(printf "%03d" "$base_name")
        new_file="${padded_number}.png"
        mv "$file" "$new_file"
    fi
done
