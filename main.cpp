#include "BigInt.h"

int main() {
    BigInt num1("123456789012345678901234567890");
    BigInt num2("987654321098765432109876543210");

    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;
    
    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    std::cout << "num1 - num2 = " << (num1 - num2) << std::endl;
    std::cout << "num1 * num2 = " << (num1 * num2) << std::endl;
    std::cout << "num1 / num2 = " << (num1 / num2) << std::endl;
    std::cout << "num1 % num2 = " << (num1 % num2) << std::endl;

    BigInt num3("10");
    std::cout << "num3^3 = " << num3.pow(3) << std::endl;
    std::cout << "10! = " << num3.factorial() << std::endl;

    BigInt num4("48");
    BigInt num5("18");
    std::cout << "gcd(48, 18) = " << num4.gcd(num5) << std::endl;
    std::cout << "lcm(48, 18) = " << num4.lcm(num5) << std::endl;

    return 0;
}
