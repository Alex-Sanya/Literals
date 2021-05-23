#include "unsignedll.hpp"
#include <string>
#include <iostream>
using namespace std;
int main() {
    cout << "Enter expressions in the format: <number1> <operator> <number2> " << endl;
    cout << "Supported operators: +, -, *, /, %, >, <, ==, != " << endl;
    while (true)
    {
        string operate;
        UnsignedLL number1, number2;
        cout << "> ";
        cin >> number1 >> operate >> number2;
        if (operate == "+") {
            cout << "Result: " << number1 + number2 << endl;
        }
        else if (operate == "-") {
            cout << "Result: " << number1 - number2 << endl;
        }
        else if (operate == "*") {
            cout << "Result: " << number1 * number2 << endl;
        }
        else if (operate == "/") {
            cout << "Result: " << number1 / number2 << endl;
        }
        else if (operate == "%") {
            cout << "Result: " << number1 % number2 << endl;
        }
        else if (operate == ">") {
            cout << "Result: " << (number1 > number2 ? "True" : "False") << endl;
        }
        else if (operate == "<") {
            cout << "Result: " << (number1 < number2 ? "True" : "False") << endl;
        }
        else if (operate == "==") {
            cout << "Result: " << (number1 == number2 ? "True" : "False") << endl;
        }
        else if (operate == "!=") {
            cout << "Result: " << (number1 != number2 ? "True" : "False") << endl;
        }
        else {
            cout << "Wrong Input!" << endl;
        }
    }
}