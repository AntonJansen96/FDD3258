#include <stdio.h>

// Theards per block
#ifndef TPB
#define TPB 256
#endif

// Blocks
#ifndef NB
#define NB 1
#endif

__global__ void helloWorldKernel();

int main()
{
	
	// Launch kernel
	helloWorldKernel<<<NB, TPB>>>();

	// Syncronize
	cudaDeviceSynchronize();

	return 0;

}

__global__ void helloWorldKernel()
{
	const int th_idx = blockIdx.x*blockDim.x + threadIdx.x;
	printf("Hello World! My threadId is %d\n", th_idx);
}
