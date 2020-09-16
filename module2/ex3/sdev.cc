#include "main.ih"

double compSdev(std::vector<double> const &input)
{
    double const mean = compMean(input);
    
    double sdev = 0;
    for (double element : input)
        sdev += (element - mean) * (element - mean);
    
    sdev /= input.size() - 1;

    return sqrt(sdev);
}