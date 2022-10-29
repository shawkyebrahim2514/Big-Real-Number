

#include "BigDecimalInt.h"
#include <iostream>


int BigDecimalInt::isValidNumber(const std::string &number) {
    int start;
    if(number[0] == '-' || number[0] == '+') start = 1;
    else start = 0;
    for (int i = start; i < number.size(); ++i)
    {
        if(number[i] < '0' || number[i] > '9')
        {
            this->sign = true;
            this->wholeNumber = {0};
            return -1;
        }
    }
    return start;
}

void BigDecimalInt::deleteZerosFromLeft() {
    // delete leading zeros from the beginning of the wholeNumber (from right)
    while (this->wholeNumber.size() > 1 && !this->wholeNumber.front())
        this->wholeNumber.pop_front();
    if(this->wholeNumber.size() == 1 && !this->wholeNumber[0]) this->sign = true;
}

void BigDecimalInt::setNumber(const std::string& number) {
    int start = isValidNumber(number);
    if(!~start) return;
    // add the sign
    if(start)
    {
        if(number[0] == '+') this->sign = true;
        else this->sign = false;
    }
    else this->sign = true;
    // append each digit to the class wholeNumber deque
    for (int i = start; i < number.size(); ++i)
    {
        this->wholeNumber.push_back(number[i]-'0');
    }
    deleteZerosFromLeft();
}

BigDecimalInt::BigDecimalInt(const int& number)
{
    std::string numberString = std::to_string(number);
    setNumber(numberString);
}

BigDecimalInt::BigDecimalInt(const std::string& number)
{
    setNumber(number);
}

BigDecimalInt::BigDecimalInt(const BigDecimalInt &anotherNumber) {
    *this = anotherNumber;
}

BigDecimalInt::BigDecimalInt(BigDecimalInt &&anotherNumber) noexcept {
    *this = anotherNumber;
}

void BigDecimalInt::clear() {
    this->wholeNumber.clear();
    this->sign = true;
}

bool BigDecimalInt::getSign() const {
    return this->sign;
}

std::deque<int> BigDecimalInt::getWholeNumber() const {
    return this->wholeNumber;
}

void BigDecimalInt::setWholeNumber(std::deque<int>& anotherWholeNumber) {
    this->wholeNumber = std::move(anotherWholeNumber);
}

void BigDecimalInt::doSummation(BigDecimalInt& a)
{
    // do summation between digits
    int position = (int)this->wholeNumber.size() - 1;
    while (position >= 0){
        this->wholeNumber[position] += a.wholeNumber[position];
        // if the wholeNumber is greater than 9
        // we should increase the digit before ours by one
        if(this->wholeNumber[position] > 9)
        {
            if(position - 1 >= 0) this->wholeNumber[position - 1] ++;
            else
            {
                // if we are in the first index (0) we should append this one in the front
                this->wholeNumber.push_front(1);
                this->wholeNumber[1] %= 10;
                break;
            }
            this->wholeNumber[position] %= 10;
        }
        position --;
    }
}

void BigDecimalInt::doSubtraction(BigDecimalInt& a) {
    // (this class) should have the smallest wholeNumber
    if(*this > a) swap(this->wholeNumber, a.wholeNumber);
    else this->sign = !this->sign;
    int position = (int)this->wholeNumber.size() - 1;
    while (position >= 0)
    {
        this->wholeNumber[position] = a.wholeNumber[position] - this->wholeNumber[position];
        if(this->wholeNumber[position] < 0)
        {
            if(position)
            {
                a.wholeNumber[position - 1] --;
                this->wholeNumber[position] += 10;
            }
        }
        position --;
    }
}

BigDecimalInt BigDecimalInt::operator+(BigDecimalInt a)
{
    // if the two numbers has the different sign
    // then we should do subtraction instead of summation of these two wholeNumber classes
    equalNumberLength(*this, a);
    if(this->sign != a.sign)
    {
        a.sign = this->sign;
        return (*this - a);
    }
    BigDecimalInt tmp("");
    tmp = *this;
    // make the length of the two wholeNumber classes equal each other
    // the smallest size will append zeros in front of it
    equalNumberLength(tmp, a);
    tmp.doSummation(a);
    return tmp;
}

BigDecimalInt BigDecimalInt::operator-(BigDecimalInt a)
{
    // if the two numbers has the different sign
    // then we should do summation instead of subtraction of these two wholeNumber classes
    equalNumberLength(*this, a);
    if(this->sign != a.sign)
    {
        a.sign = this->sign;
        return (*this + a);
    }
    BigDecimalInt tmp("");
    tmp = *this;
    // make the length of the two wholeNumber classes equal each other
    // the smallest size will append zeros in front of it
    equalNumberLength(tmp, a);
    tmp.doSubtraction(a);
    tmp.deleteZerosFromLeft();
    return tmp;
}

BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt& a)
{
    this->wholeNumber = a.wholeNumber;
    this->sign = a.sign;
    return *this;
}

BigDecimalInt &BigDecimalInt::operator=(BigDecimalInt &&anotherNumber) noexcept {
    this->wholeNumber = anotherNumber.wholeNumber;
    this->sign = anotherNumber.sign;
    return *this;
}

void BigDecimalInt::equalNumberLength(BigDecimalInt &a, BigDecimalInt &b)
{
    // make the length of the two wholeNumber classes equal each other
    // the smallest size will append zeros in front of it
    int dif = abs(a.wholeNumber.size() - b.wholeNumber.size());
    if(a.wholeNumber.size() < b.wholeNumber.size())
        for (int i = 0; i < dif; ++i)
            a.wholeNumber.push_front(0);
    else
        for (int i = 0; i < dif; ++i)
            b.wholeNumber.push_front(0);
}

bool BigDecimalInt::isSmallerThan(const BigDecimalInt& anotherNumber) {
    // check if (this) class is smaller than the anotherNumber class
    if(this->wholeNumber.size() != anotherNumber.wholeNumber.size())
        return (this->wholeNumber.size() < anotherNumber.wholeNumber.size());
    int length = this->wholeNumber.size();
    for (int i = 0; i < length; ++i) {
        if(this->wholeNumber[i] == anotherNumber.wholeNumber[i]) continue;
        return (this->wholeNumber[i] < anotherNumber.wholeNumber[i]);
    }
    return false;
}

bool BigDecimalInt::isGreaterThan(const BigDecimalInt& anotherNumber) {
    // check if (this) class is greater than the anotherNumber class
    if(this->wholeNumber.size() != anotherNumber.wholeNumber.size())
        return (this->wholeNumber.size() > anotherNumber.wholeNumber.size());
    int length = this->wholeNumber.size();
    for (int i = 0; i < length; ++i) {
        if(this->wholeNumber[i] == anotherNumber.wholeNumber[i]) continue;
        return (this->wholeNumber[i] > anotherNumber.wholeNumber[i]);
    }
    return false;
}

bool BigDecimalInt::operator<(const BigDecimalInt& anotherNumber)
{
    // compare the two BigDecimalNumbers and return if (this) class smaller than the authorNumber class
    if(this->sign != anotherNumber.sign)
        return this->sign < anotherNumber.sign;
    if(!this->sign){
        return this->isGreaterThan(anotherNumber);
    }else{
        return this->isSmallerThan(anotherNumber);
    }
}

bool BigDecimalInt::operator>(const BigDecimalInt& anotherNumber) {
    // compare the two BigDecimalNumbers and return if (this) class smaller than the authorNumber class
    if(this->sign != anotherNumber.sign)
        return this->sign > anotherNumber.sign;
    if(!this->sign){
        return this->isSmallerThan(anotherNumber);
    }else{
        return this->isGreaterThan(anotherNumber);
    }
}

bool BigDecimalInt::operator==(const BigDecimalInt& anotherNumber) {
    if(this->sign != anotherNumber.sign) return false;
    return this->wholeNumber == anotherNumber.wholeNumber;
}

std::ostream &operator<<(std::ostream &output, const BigDecimalInt& anotherNumber) {
    // if the number is negative, then we must print the negative sign first before the number
    if(!anotherNumber.sign) output << '-';
    for(auto val : anotherNumber.wholeNumber)
        output << val;
    return output;
}

std::istream &operator>>(std::istream &input, BigDecimalInt &number) {
    // get BigDecimalInt from user input
    std::string realNumberString;
    std::cin >> realNumberString;
    number = BigDecimalInt(realNumberString);;
    return input;
}