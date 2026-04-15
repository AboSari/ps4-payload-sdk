#!/bin/bash

# Loop through all directories in the current directory
for dir in */; do
  if [ -d "$dir" ]; then
    echo "Entering directory: $dir"
    (cd "$dir" && make clean)
  fi
done