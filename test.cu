
#include "lib.h"

#include <cuComplex.h>

__global__ void testKernel(uint16_t w, uint16_t h, uint32_t maxIter, double minRe, double maxRe, double minIm, double maxIm) {
    uint16_t x = blockIdx.x * blockDim.x + threadIdx.x;
    uint16_t y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < w && y < h)
    {
        double real = minRe + x * (maxRe - minRe) / w;
        double imag = minIm + y * (maxIm - minIm) / h;

        cuDoubleComplex constant = make_cuDoubleComplex(real, imag);
        cuDoubleComplex z = make_cuDoubleComplex(0, 0);

        uint16_t n = 0;
        for ( ; n < maxIter; ++n)
        {
            if (cuCabs(z) > 2.0)
                break;
            z = cuCadd(cuCmul(z, z), constant);
        }
    }
}



void BenchMark::benchGPU() {
    
    uint16_t WIDTH = 1920;
    uint16_t HEIGHT = 1080;
    uint32_t MAX_ITER = 500000;

    const double min_Re = -2.0;
    const double max_Re = 1.0;
    const double min_Im = -1.0;
    const double max_Im = 1.0;

    dim3 threadsPerBlock(32, 32);
    dim3 numBlocks( (WIDTH + threadsPerBlock.x - 1) / threadsPerBlock.x, 
                    (HEIGHT + threadsPerBlock.y - 1) / threadsPerBlock.y );
    
    auto start = std::chrono::high_resolution_clock().now();
    
    testKernel<<<threadsPerBlock, numBlocks>>>(
        WIDTH,
        HEIGHT,
        MAX_ITER,
        min_Re,
        max_Re,
        min_Im,
        max_Im
    );
    
    auto end = std::chrono::high_resolution_clock().now();
    std::chrono::duration<double> duration = end - start;
    
    printf("GPU - Fractal calculation took %f seconds.\n", duration.count());
        
    cudaDeviceSynchronize();
}
