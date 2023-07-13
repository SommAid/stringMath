//
// Created by Aidan Sommer on 7/12/23.
//

#include "StringNumber.h"

#include <utility>

// Constructor, checks if the user inputted in a correct number
StringNumber::StringNumber(std::string num) : a(std::move(num))
{
    if(isValid())
        std::cout << "Error:  " << num << " is not a valid number \n";
}

// Checks if the number contains invalid characters numbers can only contain ([-] | [.] | [0|1|2|3|4|5|6|7|8|9]... ) <- needs to be updated, so it's true
bool StringNumber::isValid(){
    int len = a.size();
    if(len == 0)
        return false;
    else if(len == 1 && a[0] == '-')
        return false;
    else if(a[0] == '-')
        return std::find_if(a.cbegin() + 1, a.cend(), [](auto num){return ((num > '9' || num < '0') && num != '.');}) != a.cend();
    else
        return std::find_if(a.cbegin(), a.cend(), [](auto num){return ((num > '9' || num < '0') && num != '.');}) != a.cend();
}

bool StringNumber::operator>(const StringNumber &b) {
    bool aNeg = a[0] == '-';
    bool bNeg = b.a[0] == '-';
    int lenA(a.size());
    int lenB(b.a.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) < b.a.substr(bNeg);
        } else if (aNeg) {
            return false;
        } else {
            return true;
        }
    }
    if (lenA > lenB)
        return true;
    else if (lenB > lenA)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.a.cbegin();
        iterA += aNeg;
        iterB += bNeg;
        for (; iterA != a.cend(); iterA++, iterB++) {
            if (*iterA > *iterB)
                return true;
            else if (*iterB > *iterA)
                return false;
        }
    }
    return false;
}

bool StringNumber::operator<(const StringNumber& b)
{
    bool aNeg = a[0] == '-';
    bool bNeg = b.a[0] == '-';
    int lenA(a.size());
    int lenB(b.a.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) > b.a.substr(bNeg);
        } else if (aNeg) {
            return true;
        } else {
            return false;
        }
    }
    if (lenB > lenA)
        return true;
    else if (lenA > lenB)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.a.cbegin();
        for (; iterB != b.a.cend(); iterB++, iterA++) {
            if (*iterB > *iterA)
                return true;
            else if (*iterA > *iterB)
                return false;
        }
    }
    return false;
}

bool StringNumber::operator>=(const StringNumber& b){
    return (a > b.a || a == b.a);
}
bool StringNumber::operator<=(const StringNumber& b){
    return (a < b.a || a == b.a);
}
bool StringNumber::operator==(const StringNumber& b){
    return (a == b.a);
}
std::string StringNumber::operator+(const StringNumber& b){
    return sum_str(a, b.a);
}
std::string StringNumber::operator-(const StringNumber& b){
    return sub_str(a, b.a);
}
std::string StringNumber::operator*(const StringNumber& b){
    return prod_str(a, b.a);
}
std::string StringNumber::operator/(const StringNumber& b){
    return quo_str(a, b.a);
}

// operator overloads for std::strings
bool StringNumber::operator>(const std::string& b){
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';

    int lenA(a.size());
    int lenB(b.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) < b.substr(bNeg);
        } else if (aNeg) {
            return false;
        } else {
            return true;
        }
    }
    if (lenA > lenB)
        return true;
    else if (lenB > lenA)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.cbegin();
        iterA += aNeg;
        iterB += bNeg;
        for (; iterA != a.cend(); iterA++, iterB++) {
            if (*iterA > *iterB)
                return true;
            else if (*iterB > *iterA)
                return false;
        }
    }
    return false;
}
bool StringNumber::operator<(const std::string& b){
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';
    int lenA(a.size());
    int lenB(b.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) > b.substr(bNeg);
        } else if (aNeg) {
            return true;
        } else {
            return false;
        }
    }
    if (lenB > lenA)
        return true;
    else if (lenA > lenB)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.cbegin();
        for (; iterB != b.cend(); iterB++, iterA++) {
            if (*iterB > *iterA)
                return true;
            else if (*iterA > *iterB)
                return false;
        }
    }
    return false;
}
bool StringNumber::operator>=(const std::string& b){
    return (a > b || a == b);
}
bool StringNumber::operator<=(const std::string& b){
    return (a < b || a == b);
}
bool StringNumber::operator==(const std::string& b){
    return (a == b);
}
std::string StringNumber::operator+(const std::string& b)
{
    return sum_str(a, b);
}
std::string StringNumber::operator-(const std::string& b)
{
    return sub_str(a, b);
}
std::string StringNumber::operator*(const std::string& b)
{
    return prod_str(a, b);
}
std::string StringNumber::operator/(const std::string& b)
{
    return quo_str(a, b);
}

std::string StringNumber::sqrt_str(const std::string &a, const std::string &b) {
    return std::string();
}

std::string StringNumber::sqrt_str(const StringNumber &a, const StringNumber &b) {
    return std::string();
}

static bool isZero(const std::string& number){
    bool is_end = std::find_if(number.crbegin(), number.crend(), [](auto a){return a > '0';}) == number.crend();
    return is_end;
}

static bool operator>(const std::string& a, const std::string& b) {
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';

    int lenA(a.size());
    int lenB(b.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) < b.substr(bNeg);
        } else if (aNeg) {
            return false;
        } else {
            return true;
        }
    }
    if (lenA > lenB)
        return true;
    else if (lenB > lenA)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.cbegin();
        iterA += aNeg;
        iterB += bNeg;
        for (; iterA != a.cend(); iterA++, iterB++) {
            if (*iterA > *iterB)
                return true;
            else if (*iterB > *iterA)
                return false;
        }
    }
    return false;
}
static bool operator<(const std::string& a, const std::string& b) {
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';
    int lenA(a.size());
    int lenB(b.size());
    if (aNeg || bNeg) {
        if (aNeg && bNeg) {
            return a.substr(aNeg) > b.substr(bNeg);
        } else if (aNeg) {
            return true;
        } else {
            return false;
        }
    }
    if (lenB > lenA)
        return true;
    else if (lenA > lenB)
        return false;
    else {
        auto iterA = a.cbegin();
        auto iterB = b.cbegin();
        for (; iterB != b.cend(); iterB++, iterA++) {
            if (*iterB > *iterA)
                return true;
            else if (*iterA > *iterB)
                return false;
        }
    }
    return false;
}
// does not work for with negative numbers
static std::string sum_str(const std::string& a, const std::string& b) {
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';
    // do negative check
    if (aNeg && bNeg) {
        return "-" + sum_str(a.substr(aNeg), b.substr(bNeg));
        // (-a) + (-b) == -(a + b)
    } else if (aNeg) {
        return sub_str(b, a.substr(aNeg));
        // (-a) + b == b - a
    } else if(bNeg) {
        return sub_str(a, b.substr(bNeg));
        // a + (-b) == a - b
    }
    std::string summation;
    int currSum = 0, pos;
    auto rIterA = a.crbegin();
    auto rIterB = b.crbegin();
    for (; rIterA != a.crend() && rIterB != b.crend(); rIterA++, rIterB++) {
        currSum += *rIterA - '0';
        currSum += *rIterB - '0';
        summation.insert(summation.cbegin(), (currSum % 10 + '0'));
        currSum /= 10;
    }
    for (; rIterA != a.crend(); rIterA++) {
        currSum += *rIterA - '0';
        summation.insert(summation.cbegin(), ('0' + currSum % 10));
        currSum /= 10;
    }
    if (rIterA == a.crend() && rIterB != b.crend()) {
        currSum = *rIterB++ - '0';
        summation.insert(summation.cbegin(), ('0' + currSum % 10));
        currSum /= 10;
        pos = rIterB - b.crbegin();
        summation.insert(summation.cbegin(), b.cbegin(), b.cend() - pos);
        currSum /= 10;
    }
    if (currSum) {
        summation.insert(summation.cbegin(), ('0' + currSum));
    }
    return summation;
}

// does not work when the difference is negative
static std::string sub_str(const std::string& a, const std::string& b)
{
    int negA = a[0] == '-';
    int negB = b[0] == '-';
    if(negA && negB) {
        return sub_str(b.substr(negB), a.substr(negA));
        // -a - -b == -a + b == b - a
    }
    else if(negA){
        return sum_str(a, b);
        // -a - b == -(a + b)
    }
    else if(negB) {
        return sum_str(a, b.substr(negB));
        // a - (-b) == a + b
    }
    int borrow = 0;
    std::string difference;
    auto rIterA = a.crbegin();
    auto rIterB = b.crbegin();
    if(a == b)
        return "0";
    else if(b > a)
    {
        return "-" + sub_str(b, a);
        // 5 - 10 == -1(10 - 5)
    }
    else if(a > b){
        for(; rIterB != b.crend(); rIterA++, rIterB++){
            if((*rIterA - borrow) >= *rIterB) // do the normal inplace subtraction
            {
                difference.insert(difference.cbegin(), (*rIterA - *rIterB + '0' - borrow));
                borrow = 0;
            }
            else // we need to do the borrow operation
            {
                difference.insert(difference.cbegin(), (*rIterA - *rIterB + '0' + 10 - borrow));
                borrow = 1;
            }
        }
        for(; rIterA != a.crend(); rIterA++){
            if((*rIterA - borrow) >= '0'){
                difference.insert(difference.cbegin(), (*rIterA - borrow));
                borrow = 0;
            }
            else{
                difference.insert(difference.cbegin(), *rIterA+9);
            }
        }
    }
    int pos_first_non_zero = std::find_if(difference.cbegin(), difference.cend(), [](auto& a){return a != '0';}) - difference.cbegin();
    return {difference.cbegin() + pos_first_non_zero, difference.cend()};
}

static std::string prod_str(const std::string& a, const std::string& b)
{
    bool aNeg = a[0] == '-';
    bool bNeg = b[0] == '-';
    if(aNeg && bNeg){
        return prod_str(a.substr(aNeg), b.substr(bNeg));
    }
    else if(aNeg || bNeg){
        return "-" + prod_str(a.substr(aNeg), b.substr(bNeg));
    }
    std::vector<std::string> sums;
    std::string curr, product = "0";
    int currA, currB;
    auto rIterB = b.crbegin();
    for(;rIterB != b.crend(); rIterB++){
        currB = *rIterB - '0';
        currA = 0;
        curr = "";
        auto rIterA = a.crbegin();
        for(;rIterA != a.crend(); rIterA++){
            currA += currB * (*rIterA - '0');
            curr.insert(curr.cbegin(), currA%10 + '0');
            currA /= 10;
        }
        if(currA)
            curr.insert(curr.cbegin(), currA + '0');
        curr.append(rIterB - b.crbegin(), '0');
        sums.emplace_back(curr);
    }
    for(const std::string& i : sums){
        product = sum_str(product, i);
    }
    return product;
}

static std::string quo_str(const std::string& numerator, const std::string& denominator)
{
    if(isZero(denominator))
        return "Error: Division by Zero";
    bool negNumerator = numerator[0] == '-';
    bool negDenominator = denominator[0] == '-';
    if(negNumerator && negDenominator){
        return quo_str(numerator.substr(negNumerator), denominator.substr(negDenominator));
    }
    else if(negNumerator || negDenominator)
        return "-" + quo_str(numerator.substr(negNumerator), denominator.substr(negDenominator));
    std::string currNumerator = "", quotient = "";
    auto iter = numerator.cbegin();
    int count;
    for(; iter < numerator.cend(); iter++)
    {
        count = 0;
        currNumerator += *iter;
        while (currNumerator > denominator || currNumerator == denominator) {
            count++;
            currNumerator = sub_str(currNumerator, denominator);
        }
        quotient += (count + '0');
        currNumerator = currNumerator.substr(std::find_if(currNumerator.cbegin(), currNumerator.cend(), [](auto& a){return a > '0';}) - currNumerator.cbegin());
    }
    int pos_first_non_zero = std::find_if(quotient.cbegin(), quotient.cend(), [](auto& a){return a > '0';}) - quotient.cbegin();
    return {quotient.cbegin() + pos_first_non_zero, quotient.cend()};
}

// try and make a better initial guess
static std::string sqrt_str(const std::string& a)
{
    if(a[0] == '-')
        return "Error: Square Root of a Negative Number";
    const std::string min = "2";
    if(a < min)
        return a;
    std::string myGuess = a.substr(0, a.size()/2+1);
    std::string guessAgain = quo_str(a, myGuess);
    while(myGuess > guessAgain)
    {
        myGuess = quo_str(sum_str(myGuess, guessAgain), "2");
        guessAgain = quo_str(a, myGuess);
    }
    return myGuess;
}



