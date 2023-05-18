/*
Author: João Víctor Costa de Oliveira
*/



/*
3.9. Write an MPI program that implements multiplication of a vector by a scalar
and dot product. The user should enter two vectors and a scalar, all of which
are read in by process 0 and distributed among the processes. The results are
calculated and collected onto process 0, which prints them. You can assume
that n, the order of the vectors, is evenly divisible by comm sz.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

void allocate_vector(double **local_x_pp, double **local_y_pp, int local_n, MPI_Comm comm);
void generate_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm, unsigned int seed);
void parallel_vector_scallar_product(double local_x[], double local_a, int local_n, int rank);
void parallel_vector_dot_product(double local_x[], double local_y[], double *result, int local_n, int rank);
void print_vector(double v[], int n);

int main(int argc, char** argv)
{
    int n;                // size of vectors
    int local_n;          // size of local_n
    int comm_sz;          // number of processes
    int my_rank;          // rank
    double a;             // scallar
    double *x = NULL;            // first vector
    double *y = NULL;            // second vector
    double *local_x = NULL;            // first vector
    double *local_y = NULL;            // second vector
    double result;        // result store variable
    double start;         // start of process
    double elapsed;       // elapsed time
    double local_elapsed; // local elapsed time
    double finish;        // finish time

    MPI_Init(&argc, &argv);
    MPI_Comm comm;
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    srand(time(NULL));
    unsigned int seed = time(NULL); 

    n = atoi(argv[1]);
    // n = 250000000;
    // n = 7812500;
    result = 0;
    a = atof(argv[2]);

    printf("--> n = %d\n", n);
    printf("--> a = %.3f\n", a);

    local_n = n/comm_sz;
    if(my_rank==0)
        printf("using n = %d traps\n", n);
    MPI_Barrier(comm);
    start = MPI_Wtime();

    allocate_vector(&x, &y, n, comm);
    allocate_vector(&local_x, &local_y, local_n, comm);

    generate_vector(x, local_n, n, my_rank, comm, seed);
    generate_vector(y, local_n, n, my_rank, comm, seed);

    MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, comm);
    MPI_Scatter(y, local_n, MPI_DOUBLE, local_y, local_n, MPI_DOUBLE, 0, comm);

    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, comm);

    parallel_vector_scallar_product(local_x, a, local_n, my_rank);

    double final;

    parallel_vector_dot_product(local_x, local_y, &result, local_n, my_rank);
    MPI_Reduce(&result, &final, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    finish = MPI_Wtime();

    local_elapsed = finish - start;

    MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);

    free(x);
    free(y);
    free(local_x);
    free(local_y);

    if(my_rank == 0)
    {
        printf("%e\n", elapsed);
    }

    MPI_Finalize();

    return 0;
}

void allocate_vector(double **local_x_pp, double **local_y_pp, int local_n, MPI_Comm comm)
{
    *local_x_pp = malloc(local_n * sizeof(double));
    *local_y_pp = malloc(local_n * sizeof(double));
}

void generate_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm, unsigned int seed)
{
    double *a = NULL;
    double *local_data = NULL;
    int i;


    if(my_rank==0)
    {
        a = malloc(n*sizeof(double));
        for (size_t i = 0; i < n; i++)
        {
            a[i] = ((double) random())/((double) RAND_MAX);
        }
    }
    local_data = malloc(n*sizeof(double));

    MPI_Scatter(a, local_n, MPI_DOUBLE, local_data, local_n, MPI_DOUBLE, 0, comm);

    MPI_Barrier(comm);

    MPI_Gather(local_data, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE, 0, comm);

    free(a);
    free(local_data);
}

void parallel_vector_scallar_product(double local_x[], double local_a, int local_n, int rank)
{
    for (size_t i = 0; i < local_n; i++)
    {
        local_x[i] *= local_a ; 
    }
}

void parallel_vector_dot_product(double local_x[], double local_y[], double *result, int local_n, int rank)
{
    for (size_t i = 0; i < local_n; i++)
    {
        *result += (local_y[i] * local_x[i]) + 2*sin(i)*cos(i);
    }
}

void print_vector(double v[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("[%.2f] ", v[i]);
    }
    printf("\n");
}
