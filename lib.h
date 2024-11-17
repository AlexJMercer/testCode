#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <stdio.h>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <chrono>

class BenchMark {
public:

    void bench();
    void benchMultiThread();
    void benchGPU();

};