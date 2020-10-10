#include "main.h"

void gather(int argc, char **argv)
{
    int size, rank, provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).    

    srand(seed * (rank + 1));               // Seed for this MPI process.

    int countLocal = compute(iterMax, size);

    int countLocalList[size];
    MPI_Gather(&countLocal, 1, MPI_INT, countLocalList, 1, MPI_INT, RANK::MASTER, MPI_COMM_WORLD);

    if (rank == RANK::MASTER)
    {
        int countGlobal = 0;
        for (int idx = 0; idx != size; ++idx)
            countGlobal += countLocalList[idx];

        printPi(countGlobal, iterMax);
    }

    MPI_Finalize();
}
