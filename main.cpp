#include "test.h"
#include "StringNumber.h"
#include <chrono>

// we want to add two numbers that have a decimal for example 12.2 + 13.53 == 25.73
// we can follow the same logic that we have been using however we should add the numbers to the left of the decimal
// then we should add the numbers to the right of the decimal then apend them together (ez?)
// current not too, sure how this will work for subtraction

std::string dec_summation_str(const std::string& a, const std::string& b) {
    // My Current Thought Process
    //  **12.3412     ***67.89**
    // +4567.12** or +12344.1237
    // essentially we want the two numbers to be stacked on top of each other by the decimal

    // I might make them do addition by adding together via "bubble"
    // bubbles are the "*" in the above example and assume the value 0 :
    // this way I can add two numbers together without having to worry about length
    // I wil need to implement this for non-decimal numbers, before I worry about numbers with a decimal
    std::string summation("");
    int lenA = a.size();
    int lenB = b.size();
    int lenRightDecA = a.cend() - std::find(a.cbegin(), a.cend(), '.');
    int lenRightDecB = b.cend() -  std::find(b.cbegin(), b.cend(), '.');
    int lenLeftDecA = lenA - lenRightDecA;
    int lenLeftDecB = lenB - lenRightDecB;
    /*
     * If a decimal point exists then the length to the right of the decimal includes the decimal thus is too long by 1
     * here if the length exits then we want to subtract it else we can keep it as zero
     * */
    std::string::const_reverse_iterator iterARight = a.crbegin();
    std::string::const_reverse_iterator iterBRight = b.crbegin();
    std::string::const_reverse_iterator iterADec = a.crbegin() + lenRightDecA;
    std::string::const_reverse_iterator iterBDec = b.crbegin() + lenRightDecB;

    // If the decimal point exists we don't want to go to far
    lenRightDecA = lenRightDecA ? lenRightDecA - 1 : 0;
    lenRightDecB = lenRightDecB ? lenRightDecB - 1 : 0;

    // Will do the after the decimal
    int curr = 0;
    if(lenRightDecA > 1 || lenRightDecB > 1){
        if(lenRightDecA > lenRightDecB){
            for(;*iterARight != '.'  || *iterBRight != '.';){
                if(lenRightDecA > lenRightDecB){
                    summation += *iterARight;
                    iterARight++;
                    lenRightDecA--;
                }
                else{
                    curr = *iterARight - '0' + *iterBRight - '0';
                    summation += (curr%10 + '0');
                    curr /= 10;
                    iterARight++;
                    iterBRight++;
                }
            }
        }
        else{
            for(;*iterBRight != '.' || *iterARight != '.';){
                if(lenRightDecB > lenRightDecA){
                    summation += *iterBRight;
                    iterBRight++;
                    lenRightDecB--;
                }
                else{
                    curr += (*iterARight - '0' + *iterBRight - '0');
                    summation += (curr%10 + '0');
                    curr /= 10;
                    iterARight++;
                    iterBRight++;
                }
            }
        }
        summation += '.';
    }

    // Will do addition before the decimal
    if(lenLeftDecA > lenLeftDecB) {
        for (; iterADec != a.crend();){
            if(lenLeftDecB != 0)
            {
                curr += (*iterADec - '0' + *iterBDec - '0');
                summation += (curr%10 + '0');
                curr /= 10;
                iterADec++;
                iterBDec++;
                lenLeftDecB--;
                lenLeftDecA--;
            }
            else
            {
                curr += (*iterADec - '0');
                summation += (curr%10 + '0');
                curr /= 10;
                iterADec++;
            }
        }
    }
    else{
        for(;iterBDec != b.crend();){
            if(lenLeftDecA != 0)
            {
                curr += (*iterADec - '0' + *iterBDec - '0');
                summation += (curr%10 + '0');
                curr /= 10;
                iterADec++;
                iterBDec++;
                lenLeftDecB--;
                lenLeftDecA--;
            }
            else {
                curr += (*iterBDec - '0');
                summation += (curr % 10 + '0');
                curr /= 10;
                iterBDec++;
            }
        }
    }
    if(curr == 1)
        summation += (curr+'0');
    return {summation.crbegin(), summation.crend()};


}

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    std::string a = "57512.";
    std::string b = "12.12345";
    std::cout << "Summation " << a << " + " << b << " = " << dec_summation_str(a, b) << " \n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time: " << elapsed_seconds.count() << " s\n";
    return 0;
//     int count = 0;
//     for(const std::string& number : nums) {
//         std::cout << count++ << " : " << number << " : " << StringNumber(number) / StringNumber(number) << "\n";
//     }
}

/*
 * bool operator>(const std::string& a, const std::string& b);
bool operator<(const std::string& a, const std::string& b);
std::string sum_str(const std::string& a, const std::string& b);
std::string sub_str(const std::string& a, const std::string& b);
std::string prod_str(const std::string& a, const std::string& b);
std::string quo_str(const std::string& numerator, const std::string& denominator);
std::string sqrt_str(const std::string& a, const std::string& b);

static bool isZero(const std::string& number){
    bool is_end = std::find_if(number.crbegin(), number.crend(), [](auto a){return a > '0';}) == number.crend();
    return is_end;
}

bool operator>(const std::string& a, const std::string& b) {
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
bool operator<(const std::string& a, const std::string& b) {
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
std::string sum_str(const std::string& a, const std::string& b) {
    // Modifies for Decimal Addition
    int numDigitsPostDecA = a.cend() -  std::find(a.cbegin(), a.cend(), '.');
    int numDigitsPostDecB = b.cend() -  std::find(b.cbegin(), b.cend(), '.');
    int addZeroA = 0;
    int addZeroB = 0;
    bool hasDecimal = false;
    int posDecimal;
    if(numDigitsPostDecA || numDigitsPostDecB){
        hasDecimal = true;
        // Determine the number of decimal points in the final number
        if(numDigitsPostDecB > numDigitsPostDecA) {
            addZeroA = numDigitsPostDecB - numDigitsPostDecA;
            posDecimal = b.size() - numDigitsPostDecB;
        }
        else if(numDigitsPostDecA >= numDigitsPostDecB) {
            addZeroB = numDigitsPostDecA -= numDigitsPostDecB;
            posDecimal = a.size() - numDigitsPostDecA;
        }
        a.append(addZeroA, '0');
        b.append(addZeroB, '0');
        // remove the decimal point in both we only care about the first one because a number can only have 1 decimal point :)
        if(numDigitsPostDecB)
            b.erase(std::find_if(b.begin(), b.end(), [](char currNum){return currNum == '.';}));
        if(numDigitsPostDecA)
            a.erase(std::find_if(a.begin(), a.end(), [](char currNum){return currNum == '.';}));
    }
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
std::string sub_str(const std::string& a, const std::string& b)
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

std::string prod_str(const std::string& a, const std::string& b)
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

std::string quo_str(const std::string& numerator, const std::string& denominator)
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
std::string sqrt_str(const std::string& a)
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
 * */