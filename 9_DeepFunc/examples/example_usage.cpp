#include "deepfunction.hpp"
#include <iostream>
#include <ostream>

int plusOne(int a)
{
    return a+1;
}

void plusTwo(int& a)
{
    a+=2;
}

int main()
{
    int b = 5;
    int result = deep<plusOne, 6>(b);
    std::cout << result << std::endl;
    deep<plusTwo, 3>(b);
    std::cout << b << std::endl;
}
