#include "stopwatch.h"

// Multiply Stopwatch object's time by scalar.
Stopwatch &Stopwatch::operator*=(size_t scalar)
{
    if (not d_stopped)
        throw(std::logic_error("cannot multiply running Stopwatch"));
    
    d_diff *= scalar;
    return *this;
}
