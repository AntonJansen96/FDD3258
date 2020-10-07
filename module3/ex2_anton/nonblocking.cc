#include "main.ih"

void nonblocking(int argc, char **argv)
{
    int size, rank, provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).

    srand(seed * (rank + 1));               // Seed for this MPI process.
    
    if (rank == RANK::MASTER)
    {
        std::vector<int> countLocalList(size - 1, 0);
        MPI_Request      requestList[size - 1];

        for (int idx = 1; idx != size; ++idx)
            MPI_Irecv
            (
                &countLocalList[idx - 1], 1, MPI_INT, 
                idx, 0, MPI_COMM_WORLD, &requestList[idx - 1]
            );

        int countLocal = compute(iterMax, size);

        MPI_Waitall(size - 1, requestList, MPI_STATUSES_IGNORE);

        //      computation from 0     +       sum of computations from 1-7
        printPi(countLocal + sum(countLocalList), iterMax);
    }
    
    if (rank != RANK::MASTER)
    {
        int countLocal = compute(iterMax, size);

        MPI_Send(&countLocal, 1, MPI_INT, RANK::MASTER, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
