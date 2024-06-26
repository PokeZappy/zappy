#!/bin/bash

# image_dir="day/frames_intro_old"
# output_dir="day/frames_intro"
image_dir="dawn/frames_intro_old"
output_dir="dawn/frames_intro"

logo="../textures/zappy_title_steve.png"

frame_count=49
speed=1.2

# Centre en haut
# x=420
# y=-10+100
# logo_scale_factor=4
# Gauche
x=150
y=30+${frame_count}*${speed}
logo_scale_factor=3.3

mkdir -p "$output_dir"

# Downscale the logo
temp_logo="$output_dir/temp_logo.png"
magick convert "$logo" -resize $(echo "100/$logo_scale_factor" | bc)% "$temp_logo"

y_anim=1000
frame_number=0
for img in "$image_dir"/*.png; do
    base_name=$(basename "$img")
    y_anim=$(echo "scale=2; $y_anim / 1.08" | bc)
    y_anim=$(printf "%.0f" $y_anim)
    if (( y_anim < 30 )); then
        y_anim=30
    fi
    magick composite -geometry +${x}+${y_anim} "$temp_logo" "$img" "$output_dir/$base_name"
    frame_number=$(($frame_number + 1))
    echo "Frame $frame_number: offset: $y_anim"
done

rm "$temp_logo"
