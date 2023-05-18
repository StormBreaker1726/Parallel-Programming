#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

int main()
{
    int sum, comm_sz, my_rank;
    int* a, *b;
    int* loc_a, *loc_b;
    int size = 80000;
    int chuck_sz;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    a = (int*)malloc(size*sizeof(int));
    b = (int*)malloc(size*sizeof(int));

    chuck_sz = size/comm_sz;


    for (size_t i = 0; i < size; i++)
    {
        a[i] = i;
        b[i] = i*2;
    }
    
    loc_a = (int*)malloc(chuck_sz*sizeof(int));
    loc_b = (int*)malloc(chuck_sz*sizeof(int));

    MPI_Scatter(a, chuck_sz, MPI_INT, loc_a, chuck_sz, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, chuck_sz, MPI_INT, loc_b, chuck_sz, MPI_INT, 0, MPI_COMM_WORLD);

    int loc_sum = 0;

    for (size_t i = 0; i < chuck_sz; i++)
    {
        loc_sum += loc_a[i] + loc_b[i];
    }

    MPI_Reduce(&loc_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank==0)
    {
        printf("%d\n", sum);
    }

    free(a);
    free(b);
    free(loc_a);
    free(loc_b);

    MPI_Finalize();

    return 0;
}