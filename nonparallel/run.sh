#!/bin/bash

# Remove the old output file and create the new one
if [ -e output ]
then
    rm output
    touch output
fi

echo "Clean and make"
make clean
make

# Run it for a bunch of test cases
for i in {500..1000..10}
do
    for j in {500..1000..10}
    do
        echo "$i rows $j cols"
        echo "$i,$j,`echo "$i $j" | ./matrix_multiply`" >> output
    done
done
