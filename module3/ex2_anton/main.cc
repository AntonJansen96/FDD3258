#include "stopwatch/stopwatch.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <math.h>

int main()
{
    int const iterMax = 1'000'000'000;

    Stopwatch timer(std::to_string(iterMax) + " iterations"); // Start timer.

    int count = 0;
    double x, y;
    
    // Seed
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    
    // Calculate PI following a Monte Carlo method
    for (int iter = 0; iter != iterMax; ++iter)
    {                       // Pick a random point.
        x = random() / static_cast<double>(RAND_MAX);
        y = random() / static_cast<double>(RAND_MAX);
        
        if (x*x + y*y <= 1.0)   // Avoid taking std::sqrt() !!!
            ++count;            // in this case it is not necessary + 
    }                           // math.h functions are slow!
    
    // Estimate Pi and display the result.
    double const pi = (count / static_cast<double>(iterMax)) * 4.0;

    std::cout << std::setprecision(10) << pi << '\n';

    timer.time(); // Stop timer and display time.
}
