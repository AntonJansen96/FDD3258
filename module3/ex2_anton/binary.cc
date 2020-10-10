#include "main.h"

void binary(int argc, char **argv)
{
    int size, rank, provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).

    srand(seed * (rank + 1));   // Seed for this MPI process.
    
    int countLocal = compute(iterMax, size);

    int temp, M = size, countGlobal = countLocal;
    while (M > 1)   // Binary tree
    {
        M /= 2;

        for (int num = 0; num != M; ++num)
        {
            if (rank == num)
            {
                MPI_Recv(&temp, 1, MPI_INT, num + M, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                countGlobal += temp;
                countLocal = countGlobal;
            }
            
            if (rank == num + M)
                MPI_Send(&countLocal, 1, MPI_INT, num, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == RANK::MASTER)
        printPi(countGlobal, iterMax);

    MPI_Finalize();
}
