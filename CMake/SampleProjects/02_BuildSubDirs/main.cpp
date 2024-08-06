#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "simple_math.h"
#include "simple_algo.h"
#include "json/json.h"

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

    const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
    const int rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err))
    {
        std::cout << "error" << std::endl;
        return -1;
    }

    const std::string name = root["Name"].asString();
    const int age = root["Age"].asInt();
    std::cout << name << std::endl;
    std::cout << age << std::endl;

    return 0;
}