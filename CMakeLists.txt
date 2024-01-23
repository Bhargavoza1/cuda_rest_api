# CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project(HttpServerCudaExample)

set(CMAKE_CXX_STANDARD 20)

find_package(cpprestsdk REQUIRED)

# Add CUDA support
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS})

# Specify the CUDA architecture
list(APPEND CUDA_NVCC_FLAGS -arch=sm_61)

# Add the CUDA source file
set(CUDA_SOURCE_FILES cuda_hello.cu cuda_hello.h )

# Add the CUDA executable
cuda_add_executable(HttpServerCudaExample main.cpp ${CUDA_SOURCE_FILES})

# Link against the necessary libraries
target_link_libraries(HttpServerCudaExample  cpprestsdk::cpprest)