
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Include MPI
#include <mpi.h>

#define MASTER 0

#define DEFAULT_TAG 0

#ifndef RNG_OFFSET
#define RNG_OFFSET 1234
#endif

#ifndef SEED
#define SEED 921
#endif

#ifndef NUM_ITER
#define NUM_ITER 1000000000
#endif

int main()
{
	
	// Initialize message passing
	MPI_Init(nullptr, nullptr);

	// Getting rank and size
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int local_num_iter = NUM_ITER/size;
    	int count = 0;
    	double x, y, z, pi;
    
	// Important: Multiply SEED by "rank" when you introduce MPI!
    	srand(SEED*rank+RNG_OFFSET);
    
    	// Calculate PI following a Monte Carlo method
    	for ( int iter = 0; iter < local_num_iter; iter++ )
    	{
        	// Generate random (X,Y) points
        	x = (double)random() / (double)RAND_MAX;
        	y = (double)random() / (double)RAND_MAX;
        	z = sqrt((x*x) + (y*y));
        	// Check if point is in unit circle
        	if (z <= 1.0)
        	{
            		count++;
        	}
    	}

	int count_mpi = count;

	if ( rank==MASTER )
	{
		for (int i=1; i<size; ++i)
		{
			MPI_Recv(&count_mpi, 1, MPI_INT, i, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			count += count_mpi;
		}
	}
	else
		MPI_Send(&count_mpi, 1, MPI_INT, MASTER, DEFAULT_TAG, MPI_COMM_WORLD);
    
    	// Estimate Pi and display the result
    	pi = ((double)count / (double)NUM_ITER) * 4.0;
    	
	if ( rank==MASTER )
    		printf("The result is %f\n", pi);
    	
	// Finalize message passing
	MPI_Finalize();

    	return 0;
}

