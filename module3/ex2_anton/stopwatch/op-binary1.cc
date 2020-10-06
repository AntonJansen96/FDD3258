#include "stopwatch.h"

// Add Stopwatch times.
Stopwatch &Stopwatch::operator+=(Stopwatch const &rhs)
{
    if ((not d_stopped) || (not rhs.d_stopped))
        throw(std::logic_error("cannot add running Stopwatches"));
    
    d_diff += rhs.d_diff;

    return *this;
}
