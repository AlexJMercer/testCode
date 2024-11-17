#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "lib.h"


int main()
{
    std::cout << "Hello from CPU !" << std::endl;

    BenchMark bench;
    bench.bench();
    bench.benchMultiThread();
    bench.benchGPU();

    std::cout << "Main End";

    return 0;
}

