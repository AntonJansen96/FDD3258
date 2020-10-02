#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size, provided;
                                            // Initialize MPI.
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).

    std::cout << std::string    // Insert as one string in std::cout to prevent
    {                           // simultaneous output of different parts.
        "Hello World from rank " + std::to_string(rank) +
        " from " + std::to_string(size) + " processes!\n"
    };

    MPI_Finalize();                         // Finalize MPI.
}
