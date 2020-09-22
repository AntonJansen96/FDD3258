// The code calculates a DFT of a random complex number input and 
// then an IDFT. The IDFT result should be the input vector 

// To compile with gcc
// gcc -Wall -O2 -fopenmp -o DFTW DFTW_mod.c 

// Written by stef

// Exercise

#include "stdio.h" 	// printf
#include "stdlib.h" 	// malloc and rand for instance. Rand not thread safe!
#include "time.h"   	// time(0) to get random seed
#include "math.h"  	// sine and cosine
#include "omp.h"   	// openmp library like timing

// two pi
#define PI2 6.28318530718

/*
 *	Here I added a couple of 'ifndef' in order to be able to pass the rounding
 *	error and the array size when compiling with the -D option
 */

// This for the rounding error, increasing N rounding error increases
// 0.01 precision good for N > 8000
#ifndef R_ERROR
#define R_ERROR 0.01
#endif	

#ifndef SIZE
#define SIZE 8000
#endif

// Main routine to calculate DFT
int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N);
// Set the input array with random number
int fillInput(double* xr, double* xi, int N);
// Set to zero the input vector
int setOutputZero(double* Xr_o, double* Xi_o, int N);
// Check if x = IDFT(DFT(x))
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_o, int N);
//PPrint the results of the DFT
int printResults(double* xr, double* xi, int N);

int main(int argc, char* argv[])
{
	
	/*
	 * 	Checking the predefined number of threads
	 */
	#pragma omp parallel 
	{
		int n_threads = omp_get_num_threads();
		#pragma omp master
			printf("[OMP] Number of threads = %d\n", n_threads);
	}
	// Size of input array
  	int N = SIZE;
  	printf("DFTW calculation with N = %d \n",N);
  
  	// Allocate array for input vector
  	double* xr = (double*) malloc (N *sizeof(double));
  	double* xi = (double*) malloc (N *sizeof(double));
  	fillInput(xr,xi,N);

	// For checking purposes
	double* xr_check = (double*) malloc (N *sizeof(double));
	double* xi_check = (double*) malloc (N *sizeof(double));
	setOutputZero(xr_check,xi_check,N);
	  
	// Allocate array for output vector
	double* Xr_o = (double*) malloc (N *sizeof(double));
	double* Xi_o = (double*) malloc (N *sizeof(double));
	setOutputZero(Xr_o,Xi_o,N);
      
      	// Start timer
	double start_time = omp_get_wtime();

	// DFT
	int idft = 1;
	DFT(idft,xr,xi,Xr_o,Xi_o,N);
	// IDFT
	idft = -1;
	DFT(idft,Xr_o,Xi_o,xr_check,xi_check,N);
	  
	// Stop timer
	double run_time = omp_get_wtime() - start_time;
	printf("DFTW computation in %f seconds\n",run_time);
	  
	// Check the results: easy to make correctness errors with openMP
	checkResults(xr,xi,xr_check,xi_check,Xr_o, Xi_o, N);
	
	// Print the results of the DFT
	#ifdef DEBUG
      		printResults(Xr_o,Xi_o,N);
	#endif
	  
	// Take out the garbage
	free(xr); free(xi);
	free(Xi_o); free(Xr_o);
	free(xr_check); free(xi_check);

	return 1;

}

// DFT/IDFT routine
// idft: 1 direct DFT, -1 inverse IDFT (Inverse DFT)
int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N)
{
	/*
	 * 	This is the part that needs being parallelized with openMP
	 */
	for (int k=0 ; k<N ; k++)
	{
		int n = 0;
		#pragma omp parallel private(n)
		{
			int id = omp_get_thread_num();
			int num_th = omp_get_num_threads();
			double partial_real = 0.0;
			double partial_imag = 0.0;
			for (n=id ; n<N ; n+=num_th)
			{
	        		// Real part of X[k]
	            		/* Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft*xi[n]*sin(n * k * PI2 / N); */
	            		partial_real +=  xr[n]*cos(n*k*PI2/N) + idft*xi[n]*sin(n*k*PI2/N);
				// Imaginary part of X[k]
	            		/* Xi_o[k] += -idft*xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N); */
	        		partial_imag += -idft*xr[n]*sin(n*k*PI2/N) + xi[n]*cos(n*k*PI2/N);
			}
			#pragma omp critical
			{
				Xr_o[k] += partial_real;
				Xi_o[k] += partial_imag;
			}
		}	
	}
	
	// Normalize if you are doing IDFT
	if (idft==-1)
	{	
		#pragma omp parallel for schedule(static)
		for (int n=0 ; n<N ; n++)
		{
	    		Xr_o[n] /=N;
	    		Xi_o[n] /=N;
	    	}
	}
	
	return 1; 
}
	
// Set the initial signal 
// Be careful with this 
// rand() is NOT thread safe in case
int fillInput(double* xr, double* xi, int N)
{

	srand(time(0));
	for(int n=0; n < 100000;n++) // get some random number first 
		rand();

	for(int n=0; n < N;n++)
	{
		// Generate random discrete-time signal x in range (-1,+1)
	       	// xr[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
	       	// xi[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
	       	// Constant real signal
	       	xr[n] = 1.0;
	       	xi[n] = 0.0;
	}

	return 1; 

}

// Set to zero the output vector
int setOutputZero(double* Xr_o, double* Xi_o, int N)
{
	for(int n=0; n < N;n++)
	{
		Xr_o[n] = 0.0;
	       	Xi_o[n] = 0.0; 
	}

	return 1;

}

// Check if x = IDFT(DFT(x))
int checkResults(double* xr, double* xi, double* xr_check, double* xi_check, double* Xr_o, double* Xi_o, int N)
{
	
	// x[0] and x[1] have typical rounding error problem
	// Interesting there might be a theorem on this
	for(int n=0; n < N;n++)
	{
		if (fabs(xr[n] - xr_check[n]) > R_ERROR)
		    printf("ERROR - x[%d] = %f, inv(X)[%d]=%f \n",n,xr[n], n,xr_check[n]);
		if (fabs(xi[n] - xi_check[n]) > R_ERROR)
		    printf("ERROR - x[%d] = %f, inv(X)[%d]=%f \n",n,xi[n], n,xi_check[n]);
	}
	printf("Xre[0] = %f \n",Xr_o[0]);
	/*
	 *	To be sure reduction is working on both variables
	 */
	printf("Xim[0] = %f \n",Xi_o[0]);

	return 1;

}

// Print the results of the DFT
int printResults(double* xr, double* xi, int N){

	for(int n=0; n < N;n++)
		    printf("Xre[%d] = %f, Xim[%d] = %f \n", n, xr[n], n, xi[n]);

	return 1;


}
