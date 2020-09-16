#include "main.ih"

double padded(int nThreads)
{
    std::vector<double> randList(genRandList(listSize));
    omp_set_num_threads(nThreads);

    struct tvals
    {
        int    loc = 0;
        double val = 0;
        char   pad[128];
    };

    std::vector<tvals> maxinfo(nThreads);

    Stopwatch timer;

    #pragma omp parallel shared(maxinfo)
    {
        int const id = omp_get_thread_num();

        #pragma omp for
            for (int idx = 0; idx < listSize; ++idx)
            {
                if (randList[idx] > maxinfo[id].val)
                {
                    maxinfo[id].loc = idx;
                    maxinfo[id].val = randList[idx];
                }
            }
    }

    int    mloc = maxinfo[0].loc;
    double mval = maxinfo[0].val;

    for (int thread = 1; thread != nThreads; ++thread)
        if (maxinfo[thread].val > mval)
        {
            mval = maxinfo[thread].val;
            mloc = maxinfo[thread].loc;
        }

    return timer.elapsed();
}
