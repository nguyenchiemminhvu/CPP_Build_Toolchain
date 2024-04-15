#include <iostream>
#include "simple_math.h"
#include "simple_algo.h"

int main(int argc, char** argv)
{
    // Using utility functions from simple_math library
    int a = 10;
    int b = 5;

    int sum = simple_math::add(a, b);
    int product = simple_math::multiply(a, b);
    double quotient = simple_math::divide(a, b);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;
    std::cout << "Quotient: " << quotient << std::endl;

    // Using utility functions from simple_algorithm library
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};

    int max = simple_algorithm::findMax(numbers);
    int min = simple_algorithm::findMin(numbers);
    int sumOfNumbers = simple_algorithm::sum(numbers);
    double average = simple_algorithm::average(numbers);

    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
    std::cout << "Sum of Numbers: " << sumOfNumbers << std::endl;
    std::cout << "Average: " << average << std::endl;

    return 0;
}