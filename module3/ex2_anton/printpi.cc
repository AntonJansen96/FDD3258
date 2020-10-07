#include "main.ih"

// Print Pi.
void printPi(int count, int iterMax)
{
    double const pi = 4 * (count / static_cast<double>(iterMax));

    std::cout << std::setprecision(10) << '\n' << pi << '\n';    
}
