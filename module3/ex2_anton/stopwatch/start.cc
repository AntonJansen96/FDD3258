#include "stopwatch.h"
#define timeNow std::chrono::system_clock::now()

// Start Stopwatch.
void Stopwatch::start()
{
    if (d_stopped)
    {
        d_stopped = false;
        d_start = timeNow;
    }
}
