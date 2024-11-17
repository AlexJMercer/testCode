
#include "lib.h"

#include <thread>

void BenchMark::bench()
{
    auto start = std::chrono::high_resolution_clock::now();

    int HEIGHT = 1080;
    int WIDTH = 1920;

    const double min_Re = -2.0;
    const double max_Re = 1.0;
    const double min_Im = -1.0;
    const double max_Im = 1.0;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            std::complex<double> constant(min_Re + (max_Re - min_Re) * j / WIDTH,
                                              min_Im + (max_Im - min_Im) * i / HEIGHT);
            std::complex<double> z{0.0, 0.0};

            int iterations{0};
            for (; iterations < 5000; iterations++)
            {
                z = pow(z, 2) + constant;
                if (std::norm(z) > 4)
                    break;
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "CPU - Fractal calculation took " << duration.count() << " seconds.\n";
}



void BenchMark::benchMultiThread()
{
    int HEIGHT = 1080;
    int WIDTH = 1920;

    const double min_Re = -2.0;
    const double max_Re = 1.0;
    const double min_Im = -1.0;
    const double max_Im = 1.0;
    
    auto worker = [&](int start, int end)
    {

        for (int i = start; i < end; ++i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {
                std::complex<double> constant(min_Re + (max_Re - min_Re) * j / WIDTH,
                                                  min_Im + (max_Im - min_Im) * i / HEIGHT);
                std::complex<double> z{0.0, 0.0};

                int iterations{0};
                for (; iterations < 5000; iterations++)
                {
                    z = pow(z, 2) + constant;
                    if (std::norm(z) > 4)
                        break;
                }
            }
        }
    };

    const uint32_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    uint32_t rowsPerThread = HEIGHT / numThreads;

    auto start = std::chrono::high_resolution_clock::now();
    
    for (uint32_t i = 0; i < numThreads; ++i)
    {
        uint32_t startY = i * rowsPerThread;
        uint32_t endY = (i == numThreads - 1) ? HEIGHT : startY + rowsPerThread;
        threads.emplace_back(worker, startY, endY);
    }

    for (auto &t : threads)
        if (t.joinable())
            t.join();


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "CPU MT - Fractal calculation took " << duration.count() << " seconds.\n";
}