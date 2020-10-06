#include "stopwatch.h"
#define timeNow std::chrono::system_clock::now()

// Reset Stopwatch.
void Stopwatch::reset()
{
    d_start = timeNow;
    d_diff  = 0;
}
