#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


void allocate_vector(double** local_x_pp, double** local_y_pp, int local_n);
void generate_vector(double local_a[], int n);
void serial_vector_scallar_product(double local_x[], double local_a, int local_n);
void serial_vector_dot_product(double local_x[], double local_y[], int local_n, double *result);
void print_vector(double local_z[], int n);

int main()
{
    int n;
    double a, *x, *y, result;
    double start, elapsed, local_elapsed, finish;
    srand(time(NULL));
    n = 500000000;
    result = 0;
    a = 11.58;

    start = MPI_Wtime();
    allocate_vector(&x, &y, n);

    generate_vector(x, n);
    generate_vector(y, n);

    serial_vector_scallar_product(x, a, n);
    serial_vector_dot_product(x, y, n, &result);

    finish = MPI_Wtime();

    printf("Time = %e\nResult = %.3f\n\n", (finish-start),result);

    free(x);
    free(y);

    return 0;
}

void allocate_vector(double** local_x_pp, double** local_y_pp, int local_n)
{
    *local_x_pp = malloc(local_n*sizeof(double));
    *local_y_pp = malloc(local_n*sizeof(double));
}

void generate_vector(double local_a[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        // local_a[i] = rand() % 80;
        local_a[i] = ((double) random())/((double) RAND_MAX);
    }
}

void serial_vector_scallar_product(double local_x[], double local_a, int local_n)
{
    for (size_t i = 0; i < local_n; i++)
    {
        local_x[i] = (local_x[i] * local_a);
    }
}

void serial_vector_dot_product(double local_x[], double local_y[], int local_n, double *result)
{
    for (size_t i = 0; i < local_n; i++)
    {
        *result += (local_x[i] + local_y[i]) + 2*sin(i)*cos(i); ;
    }
}

void print_vector(double local_z[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("[%.2f] ", local_z[i]);
    }
    printf("\n");
}
