//
// Created by Aidan Sommer on 7/12/23.
//

#ifndef STRINGMATH_STRINGNUMBER_H
#define STRINGMATH_STRINGNUMBER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class StringNumber {

    enum ERRORS{
        EMPTY_NUMBER,
        INVALID_NUMBER_DECIMALS,
        INVALID_NEGATIVE_LOCATION,
        INVALID_CHARACTER,
    };

    std::string a;
    std::vector<ERRORS> errors;
    void printErrors();
    bool isInvalid();
public:
    explicit StringNumber(std::string num);
    // b/c it's supposed to be "a" (which already exists in the class) + object "b" (maybe) IDK learning moment I guess :)
    // operator overloads for StringNumber Object
    bool operator>(const StringNumber& b);
    bool operator<(const StringNumber& b);
    bool operator>=(const StringNumber& b);
    bool operator<=(const StringNumber& b);
    bool operator==(const StringNumber& b);
    std::string operator+(const StringNumber& b);
    std::string operator-(const StringNumber& b);
    std::string operator*(const StringNumber& b);
    std::string operator/(const StringNumber& b);
    // not sure what I want to do with this just yet (might need to make/overload some operator) ^
    std::string sqrt_str(const StringNumber& a, const StringNumber& b);
};

static bool operator>(const std::string& a, const std::string& b);
static bool operator<(const std::string& a, const std::string& b);
static std::string sum_str(const std::string& a, const std::string& b);
static std::string sub_str(const std::string& a, const std::string& b);
static std::string prod_str(const std::string& a, const std::string& b);
static std::string quo_str(const std::string& numerator, const std::string& denominator);
static std::string sqrt_str(const std::string& a, const std::string& b);
static bool isZero(const std::string& number);


#endif //STRINGMATH_STRINGNUMBER_H
