#include "main.ih"

int main()
{   // seed
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    // Parameters:
    int const repeats = 10;
    std::vector<int> const threadList = {1, 2, 4, 8, 16, 20, 24, 28, 32};

    // Initialize timelist of size repeats.
    std::vector<double> timeList(repeats);
    Table table;

    // 1. Measure performance of serial code.
    for (double &time : timeList)
        time = serial();
    table.print(timeList, "serial", 1);

    // 2. Use omp parallel for construct to parallelize.
    for (double &time : timeList)
        time = naive(32);
    table.print(timeList, "para_naive", 32);

    // 3. Use omp critical and loop over threadList.
    for (int count : threadList)
    {
        for (double &time : timeList)
            time = critical(count);
        
        table.print(timeList, "para_critical", count);
    }

    // 4. Use temporary shared array.
    for (int count : threadList)
    {
        for (double &time : timeList)
            time = shared(count);
        
        table.print(timeList, "para_shared", count);
    }

    // 5. Use temporary shared array plus padding.
    for (int count : threadList)
    {
        for (double &time : timeList)
            time = padded(count);
        
        table.print(timeList, "para_padded", count);
    }
}
