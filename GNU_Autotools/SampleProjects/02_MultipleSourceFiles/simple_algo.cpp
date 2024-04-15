#include "simple_algo.h"
#include <algorithm>

namespace simple_algorithm
{
    int findMax(const std::vector<int>& numbers)
    {
        if (numbers.empty())
        {
            throw "Error: Empty vector!";
        }
        int max = numbers[0];
        for (int i = 1; i < numbers.size(); i++)
        {
            if (numbers[i] > max)
            {
                max = numbers[i];
            }
        }
        return max;
    }

    int findMin(const std::vector<int>& numbers)
    {
        if (numbers.empty())
        {
            throw "Error: Empty vector!";
        }
        int min = numbers[0];
        for (int i = 1; i < numbers.size(); i++)
        {
            if (numbers[i] < min)
            {
                min = numbers[i];
            }
        }
        return min;
    }

    int sum(const std::vector<int>& numbers)
    {
        int total = 0;
        for (auto num : numbers)
        {
            total += num;
        }
        return total;
    }

    double average(const std::vector<int>& numbers)
    {
        if (numbers.empty())
        {
            throw "Error: Empty vector!";
        }
        int total = sum(numbers);
        return static_cast<double>(total) / numbers.size();
    }

    std::vector<int> sort(const std::vector<int>& numbers)
    {
        std::vector<int> sortedNumbers = numbers;
        std::sort(sortedNumbers.begin(), sortedNumbers.end());
        return sortedNumbers;
    }
}