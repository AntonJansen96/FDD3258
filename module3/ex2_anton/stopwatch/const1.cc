#include "stopwatch.h"
#define timeNow std::chrono::system_clock::now()

// Construct Stopwatch object and start.
Stopwatch::Stopwatch()
:
    d_start(timeNow)
{}
