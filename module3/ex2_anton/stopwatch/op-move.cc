#include "stopwatch.h"

// Move assignment.
Stopwatch &Stopwatch::operator=(Stopwatch &&tmp)
{
    if (not tmp.d_stopped)
        throw(std::logic_error("cannot move Stopwatch object when running!"));
    
    swap(tmp);
    return *this;
}
