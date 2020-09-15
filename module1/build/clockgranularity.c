#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double mysecond();

int main(int argc, char **argv)
{
  int n;

  if (argc > 0)
    n = atoi(argv[1]);

  double *ticks = (double *)malloc(n * sizeof(double));

  for (int i = 0; i < n; ++i)
    ticks[i] = mysecond();

  double mindist = 1e10;
  double maxdist = 0;
  double dist;
  
  for (int i = 1; i < n; ++i)
  {
    dist = ticks[i] - ticks[i-1];
    
    if (dist > 0)
    {
      if (dist < mindist)
        mindist = dist;
      
      if (dist > maxdist)
        maxdist = dist;
    }
  }

  printf("# min dist = %.2e, max dist = %.2e, total time = %.2e\n",
	mindist, maxdist, ticks[n-1] - ticks[0]);
  
  for (int i = 1; i < n; ++i)
    printf("%d\t%.2e\n", i, ticks[i] - ticks[i-1]);
}

// function with timer                                                             
double mysecond()
{
  struct timeval tp;
  struct timezone tzp;
  int i;
  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
