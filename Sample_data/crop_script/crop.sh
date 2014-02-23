#!/bin/bash
width=352;
height=288;
x_offset=0;
y_offset=0;
filelist=`ls | grep '.pgm'`
for image_file in $filelist
do
  convert -crop ${width}x${height}+${x_offset}+${y_offset} \
    $image_file $image_file
done
