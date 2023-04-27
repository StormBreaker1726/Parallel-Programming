#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


void allocate_vector(double** local_x_pp, double** local_y_pp, double** local_z_pp, int local_n, MPI_Comm comm);
void generate_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm);
void parallel_vector_scallar_product(double local_x[], double local_a, int local_n);
void parallel_vector_dot_product(double local_x[], double local_y[], double _local_z[], int local_n);

int main()
{
    
    return 0;
}

void allocate_vector(double** local_x_pp, double** local_y_pp, double** local_z_pp, int local_n, MPI_Comm comm)
{

}

void generate_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm)
{

}

void parallel_vector_scallar_product(double local_x[], double local_a, int local_n)
{

}

void parallel_vector_dot_product(double local_x[], double local_y[], double _local_z[], int local_n)
{

}
