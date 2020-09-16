#ifndef INCLUDED_STOPWATCH_
#define INCLUDED_STOPWATCH_

#include <chrono>

class Stopwatch
{
    #define timePoint  std::chrono::time_point<std::chrono::system_clock>
    #define timeNow    std::chrono::system_clock::now()
    #define timeFactor std::chrono::nanoseconds(std::chrono::seconds(1)).count()
    
    private:
        timePoint d_start;
        timePoint d_stop;

    public:
        Stopwatch()
        :
            d_start(timeNow)
        {}

        // Return time elapsed between object initialization and function call.
        double elapsed();
};

inline double Stopwatch::elapsed()
{
    d_stop = timeNow;
    double diff = (d_stop - d_start).count();

    return diff / timeFactor;
}

#endif
