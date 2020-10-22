#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 10000
#endif

// Theards per block
#ifndef TPB
#define TPB 256
#endif

// DEBUG
#ifndef PRINT
#define PRINT 0
#endif

// Returns a random float between 0 and 1
float rand_float();

// Initialize a random vector of size ARRAY_SIZE
void init_rand_vec(float*);

// Serial CPU SAXPY code
void saxpy_serial_cpu(float, float*, float*);

// CUDA GPU kernel for SAXPY
__global__ void saxpyKernel(float, float*, float*);

// Compute the sum of squares mean error
float l2_avg_norm(float*, float*);

// Timing
double cpuSecond();

// For debug
void print_vector(float*);

int main()
{

	// Print array size
	printf("\nArray size = %d\n", ARRAY_SIZE);

	// Init RNG
	srand(time(0));

	float x[ARRAY_SIZE];
	float y1[ARRAY_SIZE];
	float a = rand_float();
	init_rand_vec(x);
	init_rand_vec(y1);

	if (PRINT)
	{
        	printf("\n*** Debug: print CPU init ***\n");
        	print_vector(y1);
	}

	// Init GPU x and y vectors
	float* x_gpu=NULL;	
	float* y_gpu=NULL;
	cudaMalloc(&x_gpu, ARRAY_SIZE*sizeof(float));
	cudaMalloc(&y_gpu, ARRAY_SIZE*sizeof(float));
	cudaMemcpy(x_gpu, x, ARRAY_SIZE*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(y_gpu, y1, ARRAY_SIZE*sizeof(float), cudaMemcpyHostToDevice);

	// Perform SAXPY serially on CPU
	double cpu_time_start = cpuSecond();
	saxpy_serial_cpu(a, x, y1);
	double cpu_time_elaps = cpuSecond() - cpu_time_start;
	printf("\nComputing SAXPY on the CPU… Done!\nTime CPU = %fsec\n", cpu_time_elaps);
	
	if (PRINT)
	{
		printf("\n*** Debug: print CPU result ***\n");
		print_vector(y1);
	}

	// Perform SAXPY on GPU
	double gpu_time_start = cpuSecond();
	saxpyKernel<<<(ARRAY_SIZE+TPB-1)/TPB, TPB>>>(a, x_gpu, y_gpu);
	cudaDeviceSynchronize();
	double gpu_time_elaps = cpuSecond() - gpu_time_start;
	printf("\nComputing SAXPY on the GPU… Done!\nTime GPU = %fsec\n", gpu_time_elaps);

	// Copy back to CPU
	float y2[ARRAY_SIZE];
	cudaMemcpy(y2, y_gpu, ARRAY_SIZE*sizeof(float), cudaMemcpyDeviceToHost);

	if (PRINT)
        {
        	printf("\n*** Debug: print GPU result ***\n");
        	print_vector(y2);
	}

	cudaFree(x_gpu);
	cudaFree(y_gpu);
	
	float l2_error = l2_avg_norm(y1, y2);
	printf("\nL2 norm error = %f\n", l2_error);

	return 1;

}

float rand_float()
{
	return ((float)rand()) / RAND_MAX;
}

void init_rand_vec(float* vec)
{
	for (int n = 0; n<ARRAY_SIZE; n++)
		vec[n] = rand_float();
}

void saxpy_serial_cpu(float a, float* x, float* y)
{
	for (int n=0; n<ARRAY_SIZE; n++)
		y[n] += a*x[n];
}

__global__ void saxpyKernel(float a, float* x, float* y)
{
	const int i = blockIdx.x*blockDim.x + threadIdx.x;
	y[i] += a*x[i];
	/* Test */
	// y[i] = i;
	/* **** */
}

float l2_avg_norm(float* v1, float* v2)
{
	float sum = 0.0;
	float diff;
	for (int n = 0; n < ARRAY_SIZE; n++) 
	{	
		diff = v1[n]-v2[n];
		sum += diff*diff;
	}
	return sqrt(sum)/ARRAY_SIZE;
}

double cpuSecond() 
{
  	struct timeval tp;
   	gettimeofday(&tp,NULL);
   	return ((double)tp.tv_sec + (double)tp.tv_usec*1.0e-6);
}

void print_vector(float* x)
{
	for (int n = 0; n<ARRAY_SIZE; ++n)
		printf("%f\n", x[n]);
}
