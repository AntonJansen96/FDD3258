#include "main.ih"

// 2.1 Linear.
void linear(int argc, char **argv)
{
    int size, rank, provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).

    srand(seed * (rank + 1));               // Seed for this MPI process.

    int countLocal = compute(iterMax, size);
    
    if (rank == RANK::MASTER)
    {
        int temp, countGlobal = countLocal;
        for (int idx = 1; idx != size; ++idx)
        {                       // Receive countLocal and store in temp
            MPI_Recv(&temp, 1, MPI_INT, idx, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            countGlobal += temp;
        }
    
        printPi(countGlobal, iterMax);
    }
    else                        // Send countLocal to rank 0
        MPI_Send(&countLocal, 1, MPI_INT, RANK::MASTER, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}
