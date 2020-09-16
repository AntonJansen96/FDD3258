#include "main.ih"

double serial() 
{
    std::vector<double> const randList(genRandList(listSize));

    int    maxloc = 0;
    double maxval = 0.0;

    Stopwatch timer;
    
    for (int idx = 0; idx < listSize; ++idx)
        if (randList[idx] > maxval)
        {
            maxval = randList[idx];
            maxloc = idx;
        }

    return timer.elapsed();
}
