#include <stdio.h>

__global__ void cudaHello()
{
    int const threadId = blockIdx.x * blockDim.x + threadIdx.x;
   
    printf("Hello World! My threadId is %d\n", threadId);
}

int main()
{
    int const TB = 1;       // Number of thread blocks
    int const TPB = 256;    // Number of threads per block

    cudaHello<<<TB, TPB>>>();
    cudaDeviceSynchronize();
}
