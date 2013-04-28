#!/bin/bash

# Remove the old output file and create the new one
if [ -e output ]
then
    rm outout
    touch output
fi

# Run it for a bunch of test cases
for i in seq `500 500 10000`
do
    for j in seq `500 500 10000`
    do
        echo "$i,$j"
        echo "$i $j" | ./matrix_multiply_parallel >> output
    done
done
