#include "stopwatch.h"

// Dedicated swap member.
void Stopwatch::swap(Stopwatch &other)
{
    std::swap(d_start,       other.d_start);
    std::swap(d_stop,        other.d_stop);
    std::swap(d_diff,        other.d_diff);
    std::swap(d_description, other.d_description);
    std::swap(d_stopped,     other.d_stopped);
}
