#include "BigInt.h"

// Constructors
BigInt::BigInt() : isNegative(false) {}

BigInt::BigInt(const std::string& num) {
    if (num.empty()) {
        throw std::invalid_argument("Invalid input string");
    }
    isNegative = (num[0] == '-');
    for (int i = (isNegative ? 1 : 0); i < num.size(); ++i) {
        if (!isdigit(num[i])) {
            throw std::invalid_argument("Invalid input string");
        }
        digits.push_back(num[i] - '0');
    }
    std::reverse(digits.begin(), digits.end());
    removeLeadingZeros();
}

BigInt::BigInt(long long num) {
    if (num < 0) {
        isNegative = true;
        num = -num;
    } else {
        isNegative = false;
    }
    if (num == 0) {
        digits.push_back(0);
    } else {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
}

// Helper Functions
void BigInt::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

BigInt BigInt::addAbsoluteValues(const BigInt& other) const {
    BigInt result;
    int carry = 0;
    size_t maxLength = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < maxLength || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

BigInt BigInt::subtractAbsoluteValues(const BigInt& other) const {
    // Assumes *this >= other
    BigInt result;
    int carry = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0);
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.digits.push_back(diff);
    }
    result.removeLeadingZeros();
    return result;
}

int BigInt::compareAbsoluteValues(const BigInt& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size() ? -1 : 1;
    }
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i] ? -1 : 1;
        }
    }
    return 0;
}

// Operator Overloads
BigInt BigInt::operator+(const BigInt& other) const {
    if (isNegative == other.isNegative) {
        BigInt result = addAbsoluteValues(other);
        result.isNegative = isNegative;
        return result;
    } else {
        if (compareAbsoluteValues(other) >= 0) {
            BigInt result = subtractAbsoluteValues(other);
            result.isNegative = isNegative;
            return result;
        } else {
            BigInt result = other.subtractAbsoluteValues(*this);
            result.isNegative = other.isNegative;
            return result;
        }
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        BigInt result = addAbsoluteValues(other);
        result.isNegative = isNegative;
        return result;
    } else {
        if (compareAbsoluteValues(other) >= 0) {
            BigInt result = subtractAbsoluteValues(other);
            result.isNegative = isNegative;
            return result;
        } else {
            BigInt result = other.subtractAbsoluteValues(*this);
            result.isNegative = !other.isNegative;
            return result;
        }
    }
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits.resize(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            long long cur = result.digits[i + j] +
                            digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            result.digits[i + j] = static_cast<int>(cur % 10);
            carry = static_cast<int>(cur / 10);
        }
    }
    result.isNegative = isNegative != other.isNegative;
    result.removeLeadingZeros();
    return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
    if (other == BigInt(0)) {
        throw std::runtime_error("Division by zero");
    }

    BigInt result, curValue;
    result.digits.resize(digits.size());
    for (int i = digits.size() - 1; i >= 0; --i) {
        curValue.digits.insert(curValue.digits.begin(), digits[i]);
        curValue.removeLeadingZeros();
        int x = 0, l = 0, r = 10;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInt cur = other.abs() * BigInt(m);
            if (cur <= curValue) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        result.digits[i] = x;
        curValue = curValue - other.abs() * BigInt(x);
    }

    result.isNegative = isNegative != other.isNegative;
    result.removeLeadingZeros();
    return result;
}

BigInt BigInt::operator%(const BigInt& other) const {
    BigInt quotient = *this / other;
    BigInt remainder = *this - (quotient * other);
    return remainder;
}

bool BigInt::operator==(const BigInt& other) const {
    return isNegative == other.isNegative && digits == other.digits;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        return isNegative;
    }
    if (isNegative) {
        return compareAbsoluteValues(other) > 0;
    }
    return compareAbsoluteValues(other) < 0;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.isNegative && !(num.digits.size() == 1 && num.digits[0] == 0)) {
        os << '-';
    }
    for (int i = num.digits.size() - 1; i >= 0; --i) {
        os << num.digits[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string str;
    is >> str;
    num = BigInt(str);
    return is;
}

BigInt BigInt::abs() const {
    BigInt result = *this;
    result.isNegative = false;
    return result;
}

BigInt BigInt::pow(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Exponent cannot be negative");
    }
    BigInt result = 1;
    BigInt base = *this;
    while (exponent) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent /= 2;
    }
    return result;
}

BigInt BigInt::factorial() const {
    if (*this < BigInt(0)) {
        throw std::invalid_argument("Factorial of negative number is undefined");
    }
    BigInt result = 1;
    for (BigInt i = 1; i <= *this; i = i + 1) {
        result = result * i;
    }
    return result;
}

BigInt BigInt::gcd(const BigInt& other) const {
    BigInt a = *this;
    BigInt b = other;
    while (b != BigInt(0)) {
        BigInt temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

BigInt BigInt::lcm(const BigInt& other) const {
    return (*this * other).abs() / gcd(other);
}
