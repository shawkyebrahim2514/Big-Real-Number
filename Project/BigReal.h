/*
 * BigReal class is a big container of the fraction numbers
 * can do summation or subtraction on these classes
 * it depends on BigDecimalInt class
 * can be created from string, float number, integer number, BigDecimalInt number or another BigReal number
*/

#ifndef TASK_1_BIGREAL_H
#define TASK_1_BIGREAL_H
#include "BigDecimalInt.h"

class BigReal {
private:
    int decimalPointPosition;
    BigDecimalInt decimalNumber;
    bool checkValidInput(const std::string& input);
    void setNumber(const std::string& realNumber);
    void deleteZerosFromFractionPart();
    void addZerosToFractionPart(BigReal& realNumber, int times);
    void equalFractionPartLength(BigReal& firstNumber, BigReal& secondNumber);
public:
    explicit BigReal (double realNumber = 0.0);
    explicit BigReal (const std::string& realNumber);
    explicit BigReal (const BigDecimalInt& bigInteger);
    BigReal (const BigReal& anotherReal);
    BigReal (BigReal&& anotherReal) noexcept ;
    BigReal& operator= (const BigReal& anotherReal);
    BigReal& operator= (BigReal&& anotherReal) noexcept ;
    BigReal operator+ (const BigReal& anotherReal);
    BigReal operator- (const BigReal& anotherReal);
    bool operator< (const BigReal& anotherReal);
    bool operator> (const BigReal& anotherReal);
    bool operator== (const BigReal& anotherReal);
    friend std::ostream& operator << (std::ostream& output, const BigReal& num);
    friend std::istream& operator >> (std::istream& input, BigReal& num);
};

#endif