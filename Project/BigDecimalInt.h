/*
 * BigDecimalInt class is a big container of the integer numbers
 * can do summation or subtraction on these classes
 * can be created from string, integer number or another BigDecimalInt number
*/

#ifndef PROJECT_BIGDECIMALINT_H
#define PROJECT_BIGDECIMALINT_H
#include <deque>
#include <iostream>
#include <regex>

class BigDecimalInt {
    bool sign;
    std::deque<int> wholeNumber;
    void equalNumberLength(BigDecimalInt& a, BigDecimalInt& b);
    void deleteZerosFromLeft();
    int isValidNumber(const std::string& number);
    void doSummation(BigDecimalInt& a);
    void doSubtraction(BigDecimalInt& a);
    void setNumber(const std::string& number);
    bool isSmallerThan(const BigDecimalInt& secondNumber);
    bool isGreaterThan(const BigDecimalInt& secondNumber);
public:
    BigDecimalInt()= default;
    explicit BigDecimalInt(const int& number);
    explicit BigDecimalInt(const std::string& number);
    BigDecimalInt(const BigDecimalInt &anotherReal);
    BigDecimalInt(BigDecimalInt &&anotherNumber) noexcept;
    BigDecimalInt operator+ (BigDecimalInt anotherNumber);
    BigDecimalInt operator- (BigDecimalInt anotherNumber);
    BigDecimalInt& operator= (const BigDecimalInt& anotherNumber);
    BigDecimalInt& operator= (BigDecimalInt && anotherNumber) noexcept;
    bool operator< (const BigDecimalInt& anotherNumber);
    bool operator> (const BigDecimalInt& anotherNumber);
    bool operator== (const BigDecimalInt& anotherNumber);
    friend std::ostream& operator<<(std::ostream& output, const BigDecimalInt& number);
    friend std::istream& operator>>(std::istream& input, BigDecimalInt& number);
    void setWholeNumber(std::deque<int>& anotherWholeNumber);
    std::deque<int> getWholeNumber() const;
    void clear();
    bool getSign() const;
};

#endif
