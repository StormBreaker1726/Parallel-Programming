/* File:     mpi_trap3.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal 
 *           rule.  This version uses collective communications to 
 *           distribute the input data and compute the global sum.
 *
 * Input:    The endpoints of the interval of integration and the number
 *           of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap2 mpi_trap2.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap2
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Notes:  
 *    1. f(x) is all hardwired.
 *    2. The number of trapezoids should be evenly divisible by
 *       the number of processes.
 *
 * IPP2:  Section 3.4.2 (pp. 110 and ff.)
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>
#include <math.h>

/* Get the input values */
void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p,
      long int* n_p);

/* Calculate local integral  */
double Trap(double left_endpt, double right_endpt, long int trap_count, 
   double base_len);    

/* Function we're integrating */
double f(double x); 

/* Function that calculates factorial */
double factorial(int t)
{
	double fac = 1;
	for(int i = 1; i <= t; i++)
	{
		fac *= i;
	}
	
	return fac;
}


int main(void) {
   int my_rank, comm_sz,  local_n;
   long int n;   
   double a, b, h, local_a, local_b;
   double local_int, total_int;
   
   double local_start, local_finish, local_elapsed, elapsed_max, elapsed_min;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   Get_input(my_rank, comm_sz, &a, &b, &n);

   h = (b-a)/n;          /* h is the same for all processes */
   local_n = n/comm_sz;  /* So is the number of trapezoids  */
   long int resto = n % comm_sz;
   /* Length of each process' interval of
    * integration = local_n*h.  So my interval
    * starts at: */
   if(my_rank < resto)
   {
	   local_n++;
	   local_a = a + my_rank*local_n*h;
   }
   else
	{
		local_a = a + (resto*(local_n+1) + (my_rank-resto) * local_n)*h;
	}
   
   local_b = local_a + local_n*h;
   MPI_Barrier(MPI_COMM_WORLD);
   local_start = MPI_Wtime();
   local_int = Trap(local_a, local_b, local_n, h);
	
   /* Add up the integrals calculated by each process */
   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
         MPI_COMM_WORLD);
	
	local_finish = MPI_Wtime();
	local_elapsed = local_finish - local_start;
	
	MPI_Reduce(&local_elapsed, &elapsed_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_elapsed, &elapsed_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	
   /* Print the result */
   if (my_rank == 0) {
      printf("With n = %d trapezoids, our estimate\n", n);
      printf("of the integral from %f to %f = %.15e\n",
          a, b, total_int);
      printf("Time max = %e seconds\n",
          elapsed_max);
	  printf("\nTime min = %e seconds\n",
		elapsed_min);
      printf("\n\n");
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

/*------------------------------------------------------------------
 * Function:     Get_input
 * Purpose:      Get the user input:  the left and right endpoints
 *               and the number of trapezoids
 * Input args:   my_rank:  process rank in MPI_COMM_WORLD
 *               comm_sz:  number of processes in MPI_COMM_WORLD
 * Output args:  a_p:  pointer to left endpoint               
 *               b_p:  pointer to right endpoint               
 *               n_p:  pointer to number of trapezoids
 */
void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p,
      long int* n_p) {

   /*if (my_rank == 0) {
      printf("Enter a, b, and n\n");
      scanf("%lf %lf %d", a_p, b_p, n_p);
   }*/
   
   *a_p = 0; 
   *b_p = 3; 
   *n_p = 20*pow(10,8);
    
   MPI_Bcast(a_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(b_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
}  /* Get_input */

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
      double left_endpt  /* in */, 
      double right_endpt /* in */, 
      long int    trap_count  /* in */, 
      double base_len    /* in */) {
   double estimate, x; 
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
	int t = x;
   return x*factorial(t);
} /* f */
