#include <iostream>
#include"big_integer.h"

int main()
{
    auto number1 = big_integer("18446744073709551615");
    auto number2 = big_integer("18446744073709551615");
    auto result = number1 + number2;
    //std::cout << result; // 193099
    std::cout << number1 << " + " << number2 << " = " << result << std::endl;
    //std::cout << std::endl;
    std::cout << number1 << " * 99 = " << number1 * 99 << std::endl;
    std::cout  << "99 * " << number1 << " = " << 99 * number1 << std::endl;
    std::cout << number1 << " * " << number2 << " = " << number1 * number2 << std::endl; 
    //INT_MAX = 2147483647
    //2147483647 * 2147483647 = 4 611 686 014 132 420 609
    //ULLONG_MAX = 18446744073709551615
}
