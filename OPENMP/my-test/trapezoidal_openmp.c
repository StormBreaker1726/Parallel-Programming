#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define E 2.71828

double f(double x) {
  return (sin(x)*pow(x, 2) + tan(x*2)) ; // The function to integrate
}

double trapezoidal_rule(double a, double b, int n, int num_threads) {
    double h = (b - a) / n; // Step size
    double sum = (f(a) + f(b)) / 2.0; // Approximate integral

    #pragma omp parallel for num_threads(num_threads) reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h; // Final approximation
}

int main(int argc, char** argv) {
    double a = -0.487; // Lower limit of integration
    double b = +1.478; // Upper limit of integration
    int n = 150000000; // Number of intervals
    int num_threads = atoi(argv[1]); // Number of threads to use

    double start_time = omp_get_wtime();

    double result = trapezoidal_rule(a, b, n, num_threads);

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // printf("Result: %e\n", result);
    printf("%e\n", elapsed_time);

    return 0;
}
