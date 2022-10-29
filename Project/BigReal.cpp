#include "BigReal.h"
#include <iostream>

bool BigReal::checkValidInput(const std::string& input) {
    // valid input when we get a number like this (+1.1), (-1.) or (.5)
    if(input.size() == 1 && !isdigit(input[0])) return false;
    std::regex reg("[+-]?[0-9]*[.]?[0-9]*");
    return regex_match(input, reg);
}

void BigReal::deleteZerosFromFractionPart(){
    // delete zeros from the fraction part from the right
    std::deque<int> wholeNumber = this->decimalNumber.getWholeNumber();
    int remDeletion = std::min(this->decimalPointPosition, (int)wholeNumber.size()) - 1;
    while(remDeletion && wholeNumber.size() != 1 && !wholeNumber.back()){
        // pop the back if it is zero
        // and decrease the decimal point position by one
        wholeNumber.pop_back();
        this->decimalPointPosition --;
        remDeletion --;
    }
    this->decimalNumber.setWholeNumber(wholeNumber);
}

void BigReal::setNumber(const std::string& realNumber) {
    // set realNumber in the class if it is valid
    std::string wholeNumber;
    if(!checkValidInput(realNumber)){
        // if not valid, then set the number to 0, and the position of the fraction point to 1 (0.)
        wholeNumber = "0";
        this->decimalPointPosition = 1;
    }
    else{
        int length = realNumber.size();
        // get the position of the fraction point from the realNumber
        int pointPosition = find(realNumber.begin(), realNumber.end(), '.') - realNumber.begin();
        if(pointPosition == length){
            // if there isn't any fraction point in the realNumber, then its position is 1 (no fraction exist)
            // and set the whole number to the realNumber
            this->decimalPointPosition = 1;
            wholeNumber = realNumber;
        }else{
            // if there is a fraction point in the realNumber, the set its position from right (follow 1 index numbering)
            this->decimalPointPosition = length - pointPosition;
            // set the realNumber to the wholeNumber without the fraction point
            wholeNumber = realNumber.substr(0,pointPosition);
            wholeNumber += realNumber.substr(pointPosition + 1);
        }
    }
    decimalNumber = BigDecimalInt(wholeNumber);
}

BigReal::BigReal(double realNumber) {
    // if the input is double, then we must convert it first to string number
    // and call the setNumber function to put it in this class
    std::string realNumberString = std::to_string(realNumber);
    while (realNumberString.back() == '0') realNumberString.pop_back();
    setNumber(realNumberString);
}

BigReal::BigReal(const std::string& realNumber) {
    // if the input is string, call setNumber function to put it in this class
    setNumber(realNumber);
}

BigReal::BigReal(const BigDecimalInt& bigInteger) {
    // if the input is BifDecimalInt, then the fraction position is 1
    // and set is directly to our decimalNumber class variable
    this->decimalPointPosition = 1;
    this->decimalNumber = bigInteger;
}

BigReal::BigReal(const BigReal &anotherReal) {
    // if the input from BigReal as lvalue, then we copy all its content to our class
    *this = anotherReal;
}

BigReal::BigReal(BigReal &&anotherReal) noexcept {
    // if the input from BigReal rvalue, then must move all its content to our class
    *this = anotherReal;
    anotherReal.decimalPointPosition = 1;
    anotherReal.decimalNumber.clear();
}

BigReal &BigReal::operator=(const BigReal &anotherReal) {
    // assignment operator for the lvalue
    // copy all content from the anotherReal to our class
    this->decimalPointPosition = anotherReal.decimalPointPosition;
    this->decimalNumber = anotherReal.decimalNumber;
    return *this;
}

BigReal &BigReal::operator=(BigReal &&anotherReal) noexcept {
    // assignment operator for the rvalue
    // move all content from the anotherReal to our class
    this->decimalPointPosition = anotherReal.decimalPointPosition;
    this->decimalNumber = anotherReal.decimalNumber;
    anotherReal.decimalPointPosition = 1;
    anotherReal.decimalNumber.clear();
    return *this;
}

void BigReal::addZerosToFractionPart(BigReal &realNumber, int times) {
    // add zeros to the fraction part to the right
    std::deque<int> wholeNumber = realNumber.decimalNumber.getWholeNumber();
    for (int i = 0; i < times; ++i) {
        wholeNumber.push_back(0);
    }
    realNumber.decimalNumber.setWholeNumber(wholeNumber);
}

void BigReal::equalFractionPartLength(BigReal& firstNumber, BigReal& secondNumber) {
    // make the length of the fraction part of these two classes same
    if(firstNumber.decimalPointPosition < secondNumber.decimalPointPosition){
        // if the firstNumber has the small length, then we append zeros to its fraction part to have equal length
        addZerosToFractionPart(firstNumber, secondNumber.decimalPointPosition - firstNumber.decimalPointPosition);
        firstNumber.decimalPointPosition = secondNumber.decimalPointPosition;
    }else if(firstNumber.decimalPointPosition > secondNumber.decimalPointPosition){
        // if the secondNumber has the small length, then we append zeros to its fraction part to have equal length
        addZerosToFractionPart(secondNumber, firstNumber.decimalPointPosition - secondNumber.decimalPointPosition);
        secondNumber.decimalPointPosition = firstNumber.decimalPointPosition;
    }
}

BigReal BigReal::operator+(const BigReal &anotherReal) {
    // create two copying BigReal class to not edit to the original source
    BigReal firstNumber = *this;
    BigReal secondNumber = anotherReal;
    // these two classes should have the same length of the fraction part
    equalFractionPartLength(firstNumber, secondNumber);
    firstNumber.decimalNumber = firstNumber.decimalNumber + secondNumber.decimalNumber;
    // if the position of the fraction point of the firstNumber class becomes smaller than the secondNumber
    // we should make the position of the fraction point equal to the secondNumber
    if(firstNumber.decimalNumber.getWholeNumber().size() < firstNumber.decimalPointPosition)
        firstNumber.decimalPointPosition = firstNumber.decimalNumber.getWholeNumber().size();
    // if the fraction part of the firstNumber has zeros on right, we must delete them
    firstNumber.deleteZerosFromFractionPart();
    return firstNumber;
}

BigReal BigReal::operator-(const BigReal &anotherReal) {
    // create two copying BigReal class to not edit to the original source
    BigReal firstNumber = *this;
    BigReal secondNumber = anotherReal;
    // these two classes should have the same length of the fraction part
    equalFractionPartLength(firstNumber, secondNumber);
    firstNumber.decimalNumber = firstNumber.decimalNumber - secondNumber.decimalNumber;
    // if the position of the fraction point of the firstNumber class becomes smaller than the secondNumber
    // we should make the position of the fraction point equal to the secondNumber
    if(firstNumber.decimalNumber.getWholeNumber().size() < firstNumber.decimalPointPosition)
        firstNumber.decimalPointPosition = firstNumber.decimalNumber.getWholeNumber().size();
    // if the fraction part of the firstNumber has zeros on right, we must delete them
    firstNumber.deleteZerosFromFractionPart();
    return firstNumber;
}

bool BigReal::operator<(const BigReal &anotherReal) {
    // create two copying BigReal class to not edit to the original source
    BigReal firstNumber = *this;
    BigReal secondNumber = anotherReal;
    // these two classes should have the same length of the fraction part
    equalFractionPartLength(firstNumber, secondNumber);
    // compare the BigDecimalNumber variable in each of them
    return firstNumber.decimalNumber < secondNumber.decimalNumber;
}

bool BigReal::operator>(const BigReal &anotherReal) {
    // create two copying BigReal class to not edit to the original source
    BigReal firstNumber = *this;
    BigReal secondNumber = anotherReal;
    // these two classes should have the same length of the fraction part
    equalFractionPartLength(firstNumber, secondNumber);
    // compare the BigDecimalNumber variable in each of them
    return firstNumber.decimalNumber > secondNumber.decimalNumber;
}

bool BigReal::operator==(const BigReal &anotherReal) {
    // create two copying BigReal class to not edit to the original source
    BigReal firstNumber = *this;
    BigReal secondNumber = anotherReal;
    // these two classes should have the same length of the fraction part
    equalFractionPartLength(firstNumber, secondNumber);
    // compare the BigDecimalNumber variable in each of them
    return firstNumber.decimalNumber == secondNumber.decimalNumber;
}

std::ostream &operator<<(std::ostream &output, const BigReal &realNumber) {
    // output the whole number with its fraction point
    std::deque<int> wholeNumber = realNumber.decimalNumber.getWholeNumber();
    bool sign = realNumber.decimalNumber.getSign();
    // if the number is negative, we must but first the negative sign
    if(!sign) output << '-';
    // then separate the wholeNumber to integer part and fraction part to put the decimal point
    int length = wholeNumber.size();
    for (int i = 0; i <= length - realNumber.decimalPointPosition; ++i) {
        output << wholeNumber[i];
    }
    output << '.';
    for (int i = length - realNumber.decimalPointPosition + 1; i < length; ++i) {
        output << wholeNumber[i];
    }
    // is the wholeNumber is (0) or the position of the decimal point in the right most
    // then we must bust (0) after the decimal point
    if((wholeNumber.size() == 1 && !wholeNumber[0]) || realNumber.decimalPointPosition == 1) output << 0;
    return output;
}

std::istream &operator>>(std::istream &input, BigReal &number) {
    // take the BigReal class from user input
    std::string realNumberString;
    std::cin >> realNumberString;
    number = BigReal(realNumberString);
    return input;
}