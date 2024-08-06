#include "simple_math.h"
#include <cmath>

namespace simple_math
{
    int add(int a, int b)
    {
        return a + b;
    }

    int subtract(int a, int b)
    {
        return a - b;
    }

    int multiply(int a, int b)
    {
        return a * b;
    }

    double divide(int a, int b)
    {
        if (b != 0)
        {
            return static_cast<double>(a) / b;
        }
        else
        {
            throw "Error: Division by zero!";
        }
    }

    int power(int base, int exponent)
    {
        int result = 1;
        for (int i = 0; i < exponent; i++)
        {
            result *= base;
        }
        return result;
    }

    double square_root(double value)
    {
        return sqrt(value);
    }

    double sine(double angle)
    {
        return sin(angle);
    }

    double cosine(double angle)
    {
        return cos(angle);
    }

    double tangent(double angle)
    {
        return tan(angle);
    }
}