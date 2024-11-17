cmake_minimum_required(VERSION 3.20)
project(MyCUDAProject LANGUAGES CXX CUDA)

# Set C++ and CUDA standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Specify CUDA architectures for GTX 1650
set(CMAKE_CUDA_ARCHITECTURES 75)

# Add the executable
add_executable(MyCUDAProject main.cpp lib.cpp test.cu)

# Enable separable compilation for CUDA
set_target_properties(MyCUDAProject PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75"
)

# Link against CUDA runtime
target_link_libraries(MyCUDAProject PRIVATE cudart)

# MSVC-specific flags
if(MSVC)
    target_compile_options(MyCUDAProject PRIVATE
        $<$<COMPILE_LANGUAGE:CUDA>:-Xcompiler="/EHsc /W4 /O2">
    )
endif()
