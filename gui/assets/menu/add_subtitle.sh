#!/bin/bash

# Directory containing the images
image_dir="day/frames_main"
# Path to the logo file
logo="../textures/whereissteve.png"
# Output directory
output_dir="day/new_frames_main"

x=580
y=220
# Downscale factor for the logo
logo_scale_factor=1.5

# Create the output directory if it doesn't exist
mkdir -p "$output_dir"

# Downscale the logo
temp_logo="$output_dir/temp_logo.png"
magick convert "$logo" -resize $(echo "100/$logo_scale_factor" | bc)% "$temp_logo"

# # Iterate over each PNG file in the directory
# for img in "$image_dir"/*.png; do
#     # Get the base name of the image file
#     base_name=$(basename "$img")
#     # Composite the downscaled logo onto the image at the specified coordinates
#     magick composite -geometry +${x}+${y} "$temp_logo" "$img" "$output_dir/$base_name"
# done

magick composite -geometry +${x}+${y} "$temp_logo" "$image_dir/001.png" "$output_dir/001.png"


# Remove the temporary downscaled logo
rm "$temp_logo"

echo "Logo downscaled by a factor of $logo_scale_factor and added to all images at position ($x, $y) successfully."
