#include "stopwatch.h"

// Copy constructor.
Stopwatch::Stopwatch(Stopwatch const &other)
:
    d_start(other.d_start),
    d_stop(other.d_stop),
    d_diff(other.d_diff),
    d_description(other.d_description),
    d_stopped(other.d_stopped)
{
    if (not other.d_stopped)
        throw(std::logic_error("cannot initialize Stopwatch object with a running one!"));
}
