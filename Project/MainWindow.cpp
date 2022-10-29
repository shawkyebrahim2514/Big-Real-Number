#include "MainWindow.h"
void MainWindow::showWindow() {
    paragraph(" What do you want to do? ");
    cout << "1- Add new number\n";
    cout << "2- Remove existing number\n";
    cout << "3- Edit existing number\n";
    cout << "4- Calculate the summation of two numbers\n";
    cout << "5- Calculate the subtraction of two numbers\n";
    string input;
    while (input.size() != 1 || input[0] < '1' || input[0] > '5'){
        cout << "Enter your choice: ";
        cin >> input;
    }
    if(input == "1"){
        addNumber();
    }else if(input == "2"){
        removeNumber();
    }else if(input == "3"){
        editNumber();
    }else if(input == "4"){
        summation();
    }else if(input == "5"){
        subtraction();
    }
}

MainWindow::MainWindow() {
    while (true){
        showWindow();
        string input;
        paragraph(" Do you want to do more operations? y(yes) | n(no) ");
        while (input != "y" && input != "n" && input != "yes" && input != "no"){
            cout << "Enter your choice: ";
            cin >> input;
        }
        if(input == "n" || input == "no") return;
    }
}

void MainWindow::addNumber() {
    string number;
    while (true){
        cout << "Enter number: ";
        cin >> number;
        if(!validNumber(number)) continue;
        BigReal newNumber(number);
        numbers.push_back(newNumber);
        break;
    }
}

bool MainWindow::validNumber(string& number) {
    if(number.size() == 1 && !isdigit(number[0])) return false;
    std::regex reg("[+-]?[0-9]*[.]?[0-9]*");
    return regex_match(number, reg);
}

void MainWindow::removeNumber() {
    if(!showNumbers()) return;
    int input = -1;
    while (!~input){
        cout << "Enter number list to remove: ";
        cin >> input;
        if(input < 1 || input > numbers.size()){
            cout << "Enter correct choice!\n";
            input = -1;
        }
    }
    numbers.erase(numbers.begin() + input - 1);
    paragraph(" Successfully deletion! ");
}

bool MainWindow::showNumbers() {
    if(numbers.empty()){
        paragraph(" You don't have any number yet ");
        return 0;
    }
    paragraph("");
    for (int i = 0; i < numbers.size(); ++i) {
        cout << i + 1 << " - (" << numbers[i] << ")\n";
    }
    return 1;
}

void MainWindow::editNumber() {
    if(!showNumbers()) return;
    int input = -1;
    while (!~input){
        cout << "Enter number list to edit: ";
        cin >> input;
        if(input < 1 || input > numbers.size()){
            cout << "Enter correct choice!\n";
            input = -1;
        }
    }
    string newNumber;
    cout << "Enter the new value of the number: ";
    cin >> newNumber;
    numbers[input - 1] = BigReal(newNumber);
}

void MainWindow::summation() {
    if(!showNumbers()) return;
    int number1 = -1, number2 = -1;
    while (!~number1){
        cout << "Enter number list (first number): ";
        cin >> number1;
        if(number1 < 1 || number1 > numbers.size()){
            cout << "Enter correct choice!\n";
            number1 = -1;
        }
    }
    while (!~number2){
        cout << "Enter number list (second number): ";
        cin >> number2;
        if(number2 < 1 || number2 > numbers.size()){
            cout << "Enter correct choice!\n";
            number2 = -1;
        }
    }
    number1 --;
    number2 --;
    cout << '(' << numbers[number1] << ") + (" << numbers[number2] << ") = (" << (numbers[number1] + numbers[number2]) << ")\n";
}

void MainWindow::subtraction() {
    if(!showNumbers()) return;
    int number1 = -1, number2 = -1;
    while (!~number1){
        cout << "Enter number list (first number): ";
        cin >> number1;
        if(number1 < 1 || number1 > numbers.size()){
            cout << "Enter correct choice!\n";
            number1 = -1;
        }
    }
    while (!~number2){
        cout << "Enter number list (second number): ";
        cin >> number2;
        if(number2 < 1 || number2 > numbers.size()){
            cout << "Enter correct choice!\n";
            number2 = -1;
        }
    }
    number1 --;
    number2 --;
    cout << '(' << numbers[number1] << ") - (" << numbers[number2] << ") = (" << (numbers[number1] - numbers[number2]) << ")\n";
}

void MainWindow::paragraph(const string& tmp) {
    int width = 200;
    int part = width/2 - tmp.size()/2;
    cout << string(part, '-') << tmp << string(part, '-') << '\n';
}
