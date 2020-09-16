#include "main.ih"

std::vector<double> genRandList(int size) 
{
    std::vector<double> list(size);
    for (double &element : list)
        element = random() / randMax;
    
    return list;
}