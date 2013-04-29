#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

/**
 * This is a parallel version of a matrix multiply written in C99.
 *  It will measure the time to do the multiplication and print it to stdout.
 *  Only the time to perform the multiplication is measured, initializations
 *  are not counted.
 */

void alloc2DArray(double***, int, int);
void free2DArray(double**, int);
void init2DArray(double**, int, int);
void print2DArray(double**, int, int);
void mult2DArray(double**, double**, double**, int, int);

bool verbose = false;

int main(int argc, char** argv)
{
    // print debug info if verbose flag set
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-v", 2) == 0)
        {
            verbose = true;
        }
    }


    // size of the arrays
    int m = -1;
    int n = -1;

    //printf("Enter the sizes for M and N: ");
    scanf("%d%d", &m, &n);

    if (verbose)
    {
        printf("A will be %dx%d\n", m, n);
        printf("B will be %dx%d\n", n, m);
        printf("C will be %dx%d\n\n", m, m);
    }

    // our arrays to fill and multiply using C = A * B
    double **a = NULL;
    double **b = NULL;
    double **c = NULL;

    // allocate memory for A, B, and C
    alloc2DArray(&a, m, n);
    alloc2DArray(&b, n, m);
    alloc2DArray(&c, m, m);

    // put random values into A and B
    init2DArray(a, m, n);
    init2DArray(b, n, m);

    mult2DArray(a, b, c, m, n);

    if (verbose)
    {
        printf("A:\n");
        print2DArray(a, m, n);
        printf("B:\n");
        print2DArray(b, n, m);
        printf("C:\n");
        print2DArray(c, m, m);
    }

    free2DArray(a, m);
    free2DArray(b, n);
    free2DArray(c, m);
}

/** Allocate space for a 2D array of doubles */
void alloc2DArray(double*** arr, int height, int width)
{
    if ( (*arr = (double**)malloc(height*sizeof(double**))) == NULL)
    {
        perror("Malloc for array failed");
        exit(1);
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            if ( ((*arr)[i] = (double*)malloc(width*sizeof(double*))) == NULL)
            {
                perror("Malloc for array failed");
                exit(1);
            }
        }
    }
}

void free2DArray(double** arr, int height)
{
    for (int i = 0; i < height; i++)
        free(arr[i]);

    free(arr);
}

/** Fill the array with random double values */
void init2DArray(double** arr, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
}

/** Print the array to stdout */
void print2DArray(double** arr, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%.5lf ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Multiply two 2D arrays together using C = A * B.
 * This assumes a is M x N
 *              b is N x M
 *          and c is M x M
 * It will print the total time to do the multiplication. It uses the Unix
 * style of getting the time so it will not work on windows.
 *
 * To see which thread did which rows uncomment everything with "thread_num"
 */
void mult2DArray(double** a, double** b, double** c, int m, int n)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    //int thread_num;
    #pragma omp parallel shared(a,b,c,m,n) //private(thread_num)
    {
        //thread_num = omp_get_thread_num();
        // Parallelize by sharing iterations on the outer loop. This means
        // thread 1 could get 0:10, thread 2 gets 11:20 ... etc.
        // Using the default number of threads we get as many threads as there
        // are processors. By not declaring a chunk size it seems to give each
        // thread num_rows / num_threads. In my case 4 threads, 1000 rows,
        // so each got 250 rows.
        #pragma omp for schedule (static)
        for (int i = 0; i < m; i++)
        {
            //printf("Thread %d did row %d\n", thread_num, i);
            for (int j = 0; j < m; j++)
            {
                double cellSum = 0.0;
                for (int k = 0; k < n; k++)
                {
                    cellSum += a[i][k] * b[k][j];
                }
                c[i][j] = cellSum;
            }
        }
    }

    gettimeofday(&end, NULL);
    double microS = (double) (end.tv_usec - start.tv_usec) / 1000000;
    double numS = (double) (end.tv_sec - start.tv_sec);
    //printf("The multiplication took %lfs\n", numS + microS);
    printf("%lf", numS + microS);
}
