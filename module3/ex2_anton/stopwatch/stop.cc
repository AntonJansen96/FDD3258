#include "stopwatch.h"
#define timeNow std::chrono::system_clock::now()

// Stop Stopwatch.
void Stopwatch::stop()
{
    if (not d_stopped)
    {
        d_stop = timeNow;
        d_stopped = true;
        d_diff += (d_stop - d_start).count();
    }
}
