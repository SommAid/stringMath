#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool operator>(const std::string& a, const std::string& b)
{
    int lenA(a.size());
    int lenB(b.size());
    if(lenA > lenB)
        return true;
    else if(lenB > lenA)
        return false;
    else // means they are the same size, so we must check each posistion until they are different
    {
        auto iterA = a.cbegin();
        auto iterB = b.cbegin();
        for(;iterA != a.cend(); iterA++, iterB++)
        {
            if(*iterA > *iterB)
                return true;
            else if(*iterB > *iterA)
                return false;
        }
    }
    // If A is not greater nor less than B then !(A > B)
    return false;
}

// does not work for with negative numbers
std::string sum_str(const std::string& a = "0", const std::string& b = "0")
{
    std::string summation;
    int currSum = 0;
    auto rIterA = a.crbegin();
    auto rIterB = b.crbegin();
    for(;rIterA != a.crend() && rIterB != b.crend(); rIterA++, rIterB++)
    {
        currSum += *rIterA - '0';
        currSum += *rIterB - '0';
        summation.insert(summation.cbegin(), (currSum % 10 + '0'));
        currSum /= 10;
    }
    if(rIterB == b.crend() && rIterA != a.crend())
    {
        currSum += *rIterA++ - '0';
        summation.insert(summation.cbegin(), ('0' + currSum));
        summation.insert(summation.cbegin(), rIterA, a.crend());
        currSum /= 10;
    }
    else if(rIterA == a.crend() && rIterB != b.crend())
    {
        currSum = *rIterB++ - '0';
        summation.insert(summation.cbegin(), ('0' + currSum));
        summation.insert(summation.cbegin(), rIterB, b.crend());
        currSum /= 10;
    }
    if(currSum)
    {
      summation.insert(summation.cbegin(), ('0' + currSum));
    }
    return summation;
}

// does not work when the difference is negative
std::string sub_str(const std::string& a, const std::string& b)
{
    int lenA(a.size());
    int lenB(b.size());
    int borrow = 0;
    std::string difference;
    auto rIterA = a.crbegin();
    auto rIterB = b.crbegin();
    if(a == b)
        return "0";
    else if(a > b){
        for(; rIterB != b.crend(); rIterA++, rIterB++){
            if((*rIterA - borrow) >= *rIterB) // do the normal inplace subtraction
            {
                difference.insert(difference.cbegin(), (*rIterA - *rIterB + '0' - borrow));
                borrow = 0;
            }
            else // we need to do the borrow operation
            {
                difference.insert(difference.cbegin(), (*rIterA - *rIterB + '0' + 10));
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
    int pos_non_zero = std::find_if(difference.cbegin(), difference.cend(), [](auto& a){return a != '0';}) - difference.cbegin();
    return {difference.cbegin() + pos_non_zero, difference.cend()};
}

std::string prod_str(const std::string& a, const std::string& b)
{
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
int main() {
    std::cout << prod_str("372", "212") << std::endl;
    return 0;
}
