#include "stopwatch/stopwatch.h"

#include <iostream>
#include <iomanip>
#include <chrono>

#include <math.h>
#include <mpi.h>

#define seed std::chrono::system_clock::now().time_since_epoch().count()

int main(int argc, char **argv)
{
    int const iterMax = 1'000'000'000;
    
    int size, rank, provided;   // MPI variables.

    // Stopwatch timer(std::to_string(iterMax) + " iterations"); // Start timer.
    




    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get how many MPI processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get my rank (ID).

    srand(seed * (rank + 1)); // Seed for this MPI process.
    int const iterMaxLocal = round(iterMax / static_cast<double>(size));

    std::cout << iterMaxLocal << '\n';

    int count = 0;
    for (int iter = 0; iter != iterMaxLocal; ++iter)
    {                           // Pick a random point.
        double x = random() / static_cast<double>(RAND_MAX);
        double y = random() / static_cast<double>(RAND_MAX);
        
        if (x*x + y*y <= 1.0)   // Avoid taking std::sqrt() !!!
            ++count;            // in this case it is not necessary + 
    }                           // math.h functions are often very slow!

    MPI_Send(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    MPI_Finalize();             // Finalize MPI.






                                // Estimate Pi and display the result.
    double const pi = (count / static_cast<double>(iterMax)) * 4.0;

    std::cout << std::setprecision(10) << pi << '\n';

    // timer.time(); // Stop timer and display time.
}
