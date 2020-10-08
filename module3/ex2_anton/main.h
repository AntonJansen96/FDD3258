#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <numeric>
#include <mpi.h>

#define seed std::chrono::system_clock::now().time_since_epoch().count()

int const iterMax = 1'000'000'000;

// Perform our Monte-Carlo calculation.
int compute(int iterMax, int size);

// Print Pi.
void printPi(int count, int iterMax);

// Serial.
void serial();

// 2.1 Linear.
void linear(int argc, char **argv);

// 2.2 Binary.
void binary(int argc, char **argv);

// 2.3 Non-blocking.
void nonblocking(int argc, char **argv);

// 2.4 Gather.
void gather(int argc, char **argv);

// 2.5 Reduce.
void reduce(int argc, char **argv);

// Returns sum of elements in abstract container.
template <typename Type> typename Type::value_type sum(Type const &input)
{
    return std::accumulate
    (
        input.begin(), input.end(), typename Type::value_type()
    );
}

enum RANK
{
    MASTER = 0
};

enum operationMode
{
    SERIAL      = 0,
    LINEAR      = 1,
    BINARY      = 2,
    NONBLOCKING = 3,
    GATHER      = 4,
    REDUCE      = 5
};
