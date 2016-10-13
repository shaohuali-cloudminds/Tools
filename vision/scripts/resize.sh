#!/bin/bash
FILES=/home/shaohua/Workspace/Projects/tools/video_images/data/right/*
for file in $FILES
do
	convert $file -resize 50% $file
#	echo $file
done
