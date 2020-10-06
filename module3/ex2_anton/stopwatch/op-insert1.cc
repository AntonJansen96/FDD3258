#include "stopwatch.h"

// Insert Stopwatch time into stream.
std::ostream &operator<<(std::ostream &out, Stopwatch &obj)
{
    obj.time(out);
    return out;
}
