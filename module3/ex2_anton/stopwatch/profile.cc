#include "stopwatch.h"

// Additional function that maybe be used for profiling functions/lambdas.
void profile(size_t iterations, void (*func)())
{
    Stopwatch timer1; timer1.stop(); timer1.reset();
    Stopwatch timer2; timer2.stop(); timer2.reset();

    for (size_t idx = 0; idx != iterations; ++idx)
    {
        // Log execution time of func + calling .start() and .stop().
        timer1.start(); func(); timer1.stop();

        // Log execution time of just calling .start() and .stop().
        timer2.start(); timer2.stop();        
    }
    // Subtract to get execution time of just func.
    ((timer1 - timer2) /= iterations).time();
}
