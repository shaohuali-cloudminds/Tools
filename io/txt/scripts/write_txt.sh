#!/bin/bash

# edit these to line to specific paths
FILES= "..."
OUTPUT= "..."

for file in $FILES
do
		echo $file >> $OUTPUT
done
