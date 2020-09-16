#include <omp.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>

size_t const listSize = 1'000'000;
size_t const repeats  = 100'000;
double const randMax  = static_cast<double>(RAND_MAX);

class Stopwatch // Good.
{
    #define timePoint  std::chrono::time_point<std::chrono::system_clock>
    #define timeNow    std::chrono::system_clock::now()
    #define timeFactor std::chrono::nanoseconds(std::chrono::seconds(1)).count()
    
    private:
        timePoint d_start, d_stop;

    public:
        Stopwatch()         // Construct Stopwatch object and start.
        :
            d_start(timeNow)
        {}

        void stop()         // Stop.
        {
            d_stop = timeNow;
        }

        double elapsed()    // Return elapsed time in (s) as a double.
        {
            double diff = (d_stop - d_start).count();

            return diff / timeFactor;
        }
};

double compMean(std::vector<double> const &input) // Good
{
    double mean = 0;
    for (auto element : input)
        mean += element;
    
    return mean / input.size();
}

double compSdev(std::vector<double> const &input) // Good
{
    double const mean = compMean(input);
    
    double sdev = 0;
    for (auto element : input)
        sdev += (element - mean) * (element - mean);
    
    sdev /= input.size() - 1;

    return sqrt(sdev);
}

std::vector<double> genRandList(size_t size) // Good
{
    std::vector<double> list(size);
    for (auto &element : list)
        element = random() / randMax;
    
    return list;
}

void printResult(std::vector<double> const &timeList, std::string message) // Good
{
    std::cout << std::setprecision(3) << message << " mean = "
              << compMean(timeList)   << "s, sdev = "
              << compSdev(timeList)   << "s\n";
}

double serial() // Good
{
    std::vector<double> const randList(genRandList(listSize));

    int    maxloc = 0;
    double maxval = 0.0;

    Stopwatch timer;
    
    for (int idx = 0; idx != listSize; ++idx)
    {
        if (randList[idx] > maxval)
        {
            maxval = randList[idx];
            maxloc = idx;
        }
    }

    timer.stop();

    return timer.elapsed();
}

double naive()
{
    std::vector<double> const randList(genRandList(listSize));
    
    int    maxloc = 0;
    double maxval = 0.0;
    
    Stopwatch timer;

    // START LOOP CODE
    #pragma omp parallel for
        for (int idx = 0; idx != listSize; ++idx)
        {
            if (randList[idx] > maxval)
            {
                maxval = randList[idx];
                maxloc = idx;
            }
        }
    // END LOOP CODE

    timer.stop();

    return timer.elapsed();
}

double critical()
{
    std::vector<double> const randList(genRandList(listSize));
    
    int    maxloc = 0;
    double maxval = 0.0;
    
    Stopwatch timer;

    // START LOOP CODE
    #pragma omp parallel for
        for (int idx = 0; idx != listSize; ++idx)
        {
            #pragma omp critical
            {
                if (randList[idx] > maxval)
                {
                    maxval = randList[idx];
                    maxloc = idx;
                }
            }
        }
    // END LOOP CODE

    timer.stop();

    return timer.elapsed();
}

double shared()
{
    std::vector<double> const randList(genRandList(listSize));
    
    std::vector<int>    maxloc(16);
    std::vector<double> maxval(16);

    Stopwatch timer;

    // START LOOP CODE
    #pragma omp parallel shared(maxval, maxloc)
    {
        int const id = omp_get_thread_num();
        maxval[id] = -1.0e30;

        #pragma omp for
            for (int idx = 0; idx != listSize; ++idx)
            {
                if (randList[idx] > maxval[id])
                {
                    maxloc[id] = idx;
                    maxval[id] = randList[idx];
                }
            }
    }

    int mloc = maxloc[0];
    double mval = maxval[0];

    for (int thread = 1; thread != 16; ++thread)
    {
        if (maxval[thread] > mval)
        {
            mval = maxval[thread];
            mloc = maxloc[thread];
        }
    }
    // END LOOP CODE

    timer.stop();

    return timer.elapsed();
}

double padded()
{
    std::vector<double> randList(genRandList(listSize));

    struct tvals
    {
        int    loc;
        double val;
        char   pad[128];
    };

    std::vector<tvals> maxinfo(16);

    Stopwatch timer;

    // START LOOP CODE
    #pragma omp parallel shared(maxinfo)
    {
        int id = omp_get_thread_num();
        maxinfo[id].val = -1.0e30;

        #pragma omp for
            for (int idx = 0; idx != listSize; ++idx)
            {
                if (randList[idx] > maxinfo[id].val)
                {
                    maxinfo[id].loc = idx;
                    maxinfo[id].val = randList[idx];
                }
            }
    }

    int mloc = maxinfo[0].loc;
    double mval = maxinfo[0].val;

    for (int thread = 1; thread != 16; ++thread)
    {
        if (maxinfo[thread].val > mval)
        {
            mval = maxinfo[thread].val;
            mloc = maxinfo[thread].loc;
        }
    }
    // END LOOP CODE

    timer.stop();

    return timer.elapsed();
}

int main()
{                                           // Seed.
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    
    std::vector<double> timeList(repeats);  // Initialize time vector.

    size_t threads = 8;

    for (auto &time : timeList)
        time = serial();
    printResult(timeList, "serial       ");
    
    for (auto &time : timeList)
        time = naive();
    printResult(timeList, "para_naive   ");

    // for (auto &time : timeList)
    //     time = critical();
    // printResult(timeList, "para_critical");

    for (auto &time : timeList)
        time = shared();
    printResult(timeList, "para_shared  ");

    for (auto &time : timeList)
        time = padded();
    printResult(timeList, "para_padded  ");
}

// To-do:
// Add ability to loop over threads
// Run