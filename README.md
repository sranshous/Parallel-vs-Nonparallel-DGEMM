#Basic testing of the effects of parallelism#

Nothing fancy, just the very basics of Open MP.

##To run##
####Manually####
There are two ways to run it. You can go into either the parallel or
nonparallel folder and make and run it. For example in the nonparallel folder.
```
    make clean
    make
    ./matrix_multiply
```
Since we are randomly generating the matricies to multiply according to
    C = A * B
we must give them heights. The program requires an input for the height and
widths of the matricies. The print statements in the program were taken out so
I could generate the CSV files correctly, but it works as follows. You put in
two integers, an M and an N, which will be the height and width respectively
for the matrix A. Then the matrix B will have a height of N and a width of M.
This will result in a matrix C with height and width M. If you wish you can
run the program verbosely, which will output the matricies to stdout.
    ./matrix_multiply -v
####Use the script####
There is a shell script named run.sh in both folders. It is what I used to
generate the CSV files for creating the beautiful figures you will find in each
folder. This runs the program starting at 500x500 up to 1000x1000 incrementing
by 10 each time. So it will run 500:500-1000, then 510:500-1000,... up to
1000:500-1000.
