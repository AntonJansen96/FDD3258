#include "stopwatch.h"

// Move constructor.
Stopwatch::Stopwatch(Stopwatch &&tmp)
:
    d_start(tmp.d_start),
    d_stop(tmp.d_stop),
    d_diff(tmp.d_diff),
    d_description(tmp.d_description),
    d_stopped(tmp.d_stopped)        
{
    if (not tmp.d_stopped)
        throw(std::logic_error("cannot initialize Stopwatch object with a running one!"));
}
