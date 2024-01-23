// utils.h
#pragma once

#include <vector>
 
// Function to perform array summation on the GPU (CUDA)
void arraySumCUDA(const std::vector<int>& array1, const std::vector<int>& array2, std::vector<int>& result);
