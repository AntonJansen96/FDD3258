#include "stopwatch.h"

// Subtract Stopwatch times.
Stopwatch &Stopwatch::operator-=(Stopwatch const &rhs)
{
    if ((not d_stopped) || (not rhs.d_stopped))
        throw(std::logic_error("cannot subtract running Stopwatches"));
    
    d_diff -= rhs.d_diff;

    return *this;
}
