#include "stopwatch.h"

// Copy assignment.
Stopwatch &Stopwatch::operator=(Stopwatch const &other)
{
    return *this = Stopwatch{other};
}
