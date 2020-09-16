#include "main.ih"

double shared(int nThreads)
{
    std::vector<double> const randList(genRandList(listSize));
    omp_set_num_threads(nThreads);
    
    std::vector<int>    maxloc(nThreads);
    std::vector<double> maxval(nThreads, 0);

    Stopwatch timer;

    #pragma omp parallel shared(maxval, maxloc)
    {
        int const id = omp_get_thread_num();

        #pragma omp for
            for (int idx = 0; idx < listSize; ++idx)
            {
                if (randList[idx] > maxval[id])
                {
                    maxloc[id] = idx;
                    maxval[id] = randList[idx];
                }
            }
    }

    int    mloc = maxloc[0];
    double mval = maxval[0];

    for (int thread = 1; thread != nThreads; ++thread)
        if (maxval[thread] > mval)
        {
            mval = maxval[thread];
            mloc = maxloc[thread];
        }

    return timer.elapsed();
}
