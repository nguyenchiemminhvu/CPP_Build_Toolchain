#ifndef SIMPLE_ALGORITHM_H
#define SIMPLE_ALGORITHM_H

#include <vector>

namespace simple_algorithm
{
    int findMax(const std::vector<int>& numbers);
    int findMin(const std::vector<int>& numbers);
    int sum(const std::vector<int>& numbers);
    double average(const std::vector<int>& numbers);
    std::vector<int> sort(const std::vector<int>& numbers);
}

#endif