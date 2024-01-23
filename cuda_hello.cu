// cuda_sum.cu
#include "cuda_hello.h"
#include <iostream>

__global__ void arraySumKernel(const int* array1, const int* array2, int* result, size_t size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        result[tid] = array1[tid] + array2[tid];
    }
}

void arraySumCUDA(const std::vector<int>& array1, const std::vector<int>& array2, std::vector<int>& result) {
    size_t size = array1.size();
    int* d_array1, * d_array2, * d_result;

    // Allocate memory on the device
    cudaMalloc(&d_array1, size * sizeof(int));
    cudaMalloc(&d_array2, size * sizeof(int));
    cudaMalloc(&d_result, size * sizeof(int));

    // Copy input arrays to the device
    cudaMemcpy(d_array1, array1.data(), size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_array2, array2.data(), size * sizeof(int), cudaMemcpyHostToDevice);

    // Launch the CUDA kernel
    arraySumKernel<<<(size + 255) / 256, 256>>>(d_array1, d_array2, d_result, size);

    // Copy the result back to the host
    cudaMemcpy(result.data(), d_result, size * sizeof(int), cudaMemcpyDeviceToHost);

    //     // Print the result on the host side
    // std::cout << "Result from CUDA: ";
    // for (int i = 0; i < size; ++i) {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << std::endl;

    // Free device memory
    cudaFree(d_array1);
    cudaFree(d_array2);
    cudaFree(d_result);
}
