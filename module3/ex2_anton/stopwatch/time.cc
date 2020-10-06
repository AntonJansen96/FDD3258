#include "stopwatch.h"
#include <iomanip>
#define timeFactor std::chrono::nanoseconds(std::chrono::seconds(1)).count()

// Insert (current) Stopwatch time into stream (default std::cout).
void Stopwatch::time(std::ostream &out)
{
    this->stop();                   // Stop Stopwatch (if not already).

    if (not d_description.empty())  // If description was specified, print.
        out << d_description << " took ";

    double diff = d_diff / timeFactor;

    if (diff < 1 && diff >= 0.001) // ms
        out << std::setprecision(3) << diff * 1'000 << "ms\n";
    
    else if (diff < 0.001 && diff >= 0.000001) // us
        out << std::setprecision(3) << diff * 1'000'000 << "us\n";

    else if (diff < 3600 && diff >= 60) // m+s
    {
        size_t min = static_cast<size_t>(diff / 60);
        size_t sec = diff - min * 60;

        out << min << 'm' << sec << "s\n";
    }
    
    else if (diff >= 3600) // h + m + s
    {
        size_t hrs = static_cast<size_t>(diff / 3600);
        size_t min = static_cast<size_t>((diff - hrs * 3600) / 60);
        size_t sec = diff - hrs * 3600 - min * 60;

        out << hrs << 'h' << min << 'm' << sec << "s\n";
    }

    else // s
        out << std::setprecision(4) << diff << "s\n";
}
