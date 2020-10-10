#include "main.h"

void reduce(int argc, char **argv)
{
    int size, rank, provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).    

    srand(seed * (rank + 1));               // Seed for this MPI process.

    int countGlobal, countLocal = compute(iterMax, size);
    MPI_Reduce(&countLocal, &countGlobal, 1, MPI_INT, MPI_SUM, RANK::MASTER, MPI_COMM_WORLD);

    if (rank == RANK::MASTER)
        printPi(countGlobal, iterMax);

    MPI_Finalize();
}
