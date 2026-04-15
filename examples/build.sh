#!/bin/bash

# Loop through all directories in the current directory
mkdir -p results
for dir in */; do
  # Skip the results directory
  if [ "$dir" = "results/" ]; then
    continue
  fi

  if [ -d "$dir" ]; then
    echo "Entering directory: $dir"
    (
      cd "$dir" &&
      make &&
      mv *.bin ../results/ 2>/dev/null &&
      make clean
    )
  fi
done