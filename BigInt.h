#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

class BigInt {
private:
    std::vector<int> digits;
    bool isNegative;

    // Helper functions
    void removeLeadingZeros();
    BigInt addAbsoluteValues(const BigInt& other) const;
    BigInt subtractAbsoluteValues(const BigInt& other) const;
    int compareAbsoluteValues(const BigInt& other) const;

public:
    // Constructors
    BigInt();
    BigInt(const std::string& num);
    BigInt(long long num);

    // Operator overloads
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    BigInt operator%(const BigInt& other) const;

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    // Input/Output stream overloads
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend std::istream& operator>>(std::istream& is, BigInt& num);

    // Utility functions
    BigInt abs() const;
    BigInt pow(int exponent) const;
    BigInt factorial() const;
    BigInt gcd(const BigInt& other) const;
    BigInt lcm(const BigInt& other) const;
};

#endif // BIGINT_H
