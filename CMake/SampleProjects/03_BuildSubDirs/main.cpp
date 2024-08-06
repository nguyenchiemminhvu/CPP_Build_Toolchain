#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "simple_math.h"
#include "simple_algo.h"

#ifdef USE_SIMPLE_CRYPTO_LIB
#include "simplecrypto.h"
#endif

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

#ifdef USE_SIMPLE_CRYPTO_LIB
    // Using opensource prebuilt library
    const char* data = "Hello, world!";
    size_t data_len = strlen(data);
    uint8_t digest[16];

    md5((const uint8_t*)data, data_len, digest);

    printf("MD5 Digest: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", digest[i]);
    }
    printf("\n");
#endif

    return 0;
}