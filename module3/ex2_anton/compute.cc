#include "main.h"

// Perform our Monte-Carlo calculation.
int compute(int iterMax, int size)
{
    int countLocal = 0;
    for (int iter = 0; iter != iterMax / size; ++iter)
    {                           // Pick a random point.
        double x = random() / static_cast<double>(RAND_MAX);
        double y = random() / static_cast<double>(RAND_MAX);
        
        if (x * x + y * y <= 1) // Avoid taking std::sqrt() !!!
            ++countLocal;       // in this case it is not necessary + 
    }                           // math.h functions are often very slow!

    return countLocal;
}
