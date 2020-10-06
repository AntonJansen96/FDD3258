#include "stopwatch.h"

// Insert Stopwatch time into stream.
std::ostream &operator<<(std::ostream &out, Stopwatch &&obj)
{   // We need this one for rvalue references.
    obj.time(out);
    return out;
}
