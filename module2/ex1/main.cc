#include <omp.h>
#include <iostream>

using namespace std;

int main()
{
    #pragma omp parallel
    {
        // Get thread ID.
        size_t const ID = omp_get_thread_num();     
        
        // Put the output message as a whole in an (rvalue) string instead of
        // inserting it in separate parts in std::cout, i.e.
        // std::cout << "Hello World from Thread " << ID << "!\n";
        // This is to prevent asynchronous inserting into std::cout and
        // messing up the output.
        cout << string("Hello World from Thread " + to_string(ID) + "!\n");
    }       
}
