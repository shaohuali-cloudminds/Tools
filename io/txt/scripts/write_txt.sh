#!/bin/bash
FILES=/home/shaohua/Workspace/caffe/avoid_outdoor/data/set10_right/*
OUTPUT=/home/shaohua/Workspace/caffe/avoid_outdoor/data/set10_right.txt

for file in $FILES
do
		echo $file >> $OUTPUT
done
