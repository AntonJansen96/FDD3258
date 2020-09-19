#include "stdio.h"
#include "omp.h"

int main()
{

	int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int sum = 0;
	
	omp_set_num_threads(4);

	#pragma omp parallel
	{

		int ID = omp_get_thread_num();
		printf("Thread %d will do its work!\n", ID);
		#pragma omp barrier

		#pragma omp for reduction(+:sum)
		for (int i = 0; i<8; ++i)
		{
			sum += a[i];
		}

	}

	printf("sum = %d\n", sum);

	return 0;
	
}
