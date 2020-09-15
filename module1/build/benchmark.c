// Anton: I modified this script for part 3 of question 3.

#include <stdio.h>
#include <sys/time.h>

// Timer
double mysecond()
{
  struct timeval tp;
  struct timezone tzp;

  int i = gettimeofday(&tp, &tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

// Anton: I wrote this function to prevent compiler optimization.
// Sums elements in array of doubles.
double sumArray(double *array, int size)
{
  double sum = 0;
  for (int idx = 0; idx != size; ++idx)
    sum += array[idx];
  
  return sum;
}

int main()
{
  int const numRuns = 100000;         // Amount of runs to obtain average.
  int const N = 100000;               // Array size.
  
  double a[N], b[N], c[N];            // Declare arrays.
                                             
  for (int idx = 0; idx != N; ++idx)  // Initialize arrays.
  {
    a[idx] = 47.0;
    b[idx] = 3.1415;
  }

  for(int idx = 0; idx < N; ++idx)    // Run loop once to avoid cold start.
    c[idx] = a[idx] * b[idx];
  
  double const t1 = mysecond();       // Create starting time point.
  
  for (int run = 0; run != numRuns; ++run)    
    for(int idx = 0; idx != N; ++idx)
      c[idx] = a[idx] * b[idx];

  double const t2 = mysecond();       // Create ending time point.

  printf("%f, %f, %f\n", sumArray(a, N), sumArray(b, N), sumArray(c, N));
                                      // Prevent unwanted compiler optimization.
  printf("Array size: %d\n", N);
  printf("Number of runs: %d\n", numRuns);
  printf("Average execution time: %11.8f s\n", (t2 - t1)/numRuns);
}
