# CppUtility
The BigInt project leverages fundamental DSA concepts such as dynamic arrays (vectors), string manipulation, and efficient algorithms for basic arithmetic operations. This not only helps in managing large numbers but also provides a solid practice ground for implementing and understanding these fundamental DSA principles in C++.
**BigInt Library for C++**
This BigInt library provides a class to handle arbitrarily large integers in C++. It allows performing mathematical operations on numbers that exceed the size limitations of built-in integer types such as long long.

Features
-Representation of arbitrarily large integers
-Basic arithmetic operations: addition, subtraction, multiplication, division, and modulo
-Additional operations: power, factorial, greatest common divisor (GCD), least common multiple (LCM), and absolute value
-Input and output stream operators for easy reading and printing of BigInt objects

Getting Started

Prerequisites
-A C++ compiler (e.g., g++, clang++)
-C++11 or later

Installation
Clone the repository or download the source files.
Ensure you have BigInt.h and BigInt.cpp in your project directory.
Include the BigInt.h header in your source file where you want to use the BigInt class.
Compiling the Project
To compile your project, you need to include both BigInt.cpp and your main source file. For example:

Copy code: g++ -o BigIntExample main.cpp BigInt.cpp
