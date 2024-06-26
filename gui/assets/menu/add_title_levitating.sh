#!/bin/bash

# image_dir="day/frames_main_old"
# output_dir="day/frames_main"
image_dir="dawn/frames_main_old"
output_dir="dawn/frames_main"

logo="../textures/zappy_title_steve.png"

# Centre en haut
# x=420
# y=-10
# max_levitation=20
# logo_scale_factor=4
# total_frames=100
# Plutôt à gauche
x=150
y=30
max_levitation=20
logo_scale_factor=3.3
total_frames=200

mkdir -p "$output_dir"

# Downscale the logo
temp_logo="$output_dir/temp_logo.png"
magick convert "$logo" -resize $(echo "100/$logo_scale_factor" | bc)% "$temp_logo"

# Function to calculate levitation offset
calculate_levitation() {
    frame=$1
    angle=$(echo "scale=10; 2 * 3.14159 * $frame / $total_frames" | bc -l)
    levitation=$(echo "$max_levitation * s($angle)" | bc -l)
    levitation=$(printf "%.0f" $levitation)
    echo $levitation
}

frame_number=0
for img in "$image_dir"/*.png; do
    base_name=$(basename "$img")
    levitation=$(calculate_levitation $frame_number)
    new_y=$(($y + $levitation))
    magick composite -geometry +${x}+${new_y} "$temp_logo" "$img" "$output_dir/$base_name"
    frame_number=$(($frame_number + 1))
    echo "Frame $frame_number: Levitation offset: $levitation"
done

rm "$temp_logo"
