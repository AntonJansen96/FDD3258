#include "main.ih"

double naive(int nThreads)
{
    std::vector<double> const randList(genRandList(listSize));
    omp_set_num_threads(nThreads);

    int    maxloc = 0;
    double maxval = 0.0;
    
    Stopwatch timer;

    #pragma omp parallel for
        for(int idx = 0; idx < listSize; ++idx)
        {
            if (randList[idx] > maxval)
            {
                maxval = randList[idx];
                maxloc = idx;
            }
        }

    return timer.elapsed();
}
