#include "stopwatch.h"

// Divide Stopwatch object's time by scalar.
Stopwatch &Stopwatch::operator/=(size_t scalar)
{
    if (not d_stopped)
        throw(std::logic_error("cannot divide running Stopwatch"));
    
    d_diff /= scalar;
    return *this;
}
