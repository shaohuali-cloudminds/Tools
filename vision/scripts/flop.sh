#!/bin/bash
FILES=/home/shaohua/Workspace/Projects/avoid_naive/data/full/*
OUTPUT=/home/shaohua/Workspace/Projects/avoid_naive/data/flop/
for file in $FILES
do
	name=${file:55:8}
	convert $file -flop  $OUTPUT$name
done
