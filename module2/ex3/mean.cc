#include "main.ih"

double compMean(std::vector<double> const &input)
{
    double mean = 0;
    for (double element : input)
        mean += element;
    
    return mean / input.size();
}