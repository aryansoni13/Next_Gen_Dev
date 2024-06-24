#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        cout << "Error: Division by zero is not allowed." << endl;
        return numeric_limits<double>::quiet_NaN();  // Return NaN to indicate error
    }
}

int mod(int a, int b) {
    if (b != 0) {
        return a % b;
    } else {
        cout << "Error: Division by zero is not allowed." << endl;
        return 0;  // Return 0 to indicate error
    }
}

void showHistory(const vector<string>& history) {
    if (history.empty()) {
        cout << "No calculations yet." << endl;
    } else {
        cout << "Calculation History:\n";
        for (const auto& record : history) {
            cout << record << endl;
        }
    }
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen
}

int main() {
    char operation;
    double num1, num2;
    bool continueCalculation = true;
    vector<string> history;

    cout << "Welcome to the Advanced Calculator!\n";

    while (continueCalculation) {
        cout << "\nMenu:\n";
        cout << "1. Addition (+)\n";
        cout << "2. Subtraction (-)\n";
        cout << "3. Multiplication (*)\n";
        cout << "4. Division (/)\n";
        cout << "5. Modulus (%)\n";
        cout << "6. Show Calculation History\n";
        cout << "7. Clear Screen\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> operation;

        if (operation == '8') {
            continueCalculation = false;
            continue;
        } else if (operation == '6') {
            showHistory(history);
            continue;
        } else if (operation == '7') {
            clearScreen();
            continue;
        }

        cout << "Enter two numbers: ";
        while (!(cin >> num1 >> num2)) {
            cout << "Invalid input. Please enter two numbers: ";
            clearInputBuffer();
        }

        string result;
        switch(operation) {
            case '1':
                result = to_string(num1) + " + " + to_string(num2) + " = " + to_string(add(num1, num2));
                cout << result << endl;
                history.push_back(result);
                break;
            case '2':
                result = to_string(num1) + " - " + to_string(num2) + " = " + to_string(subtract(num1, num2));
                cout << result << endl;
                history.push_back(result);
                break;
            case '3':
                result = to_string(num1) + " * " + to_string(num2) + " = " + to_string(multiply(num1, num2));
                cout << result << endl;
                history.push_back(result);
                break;
            case '4':
                if (num2 != 0) {
                    result = to_string(num1) + " / " + to_string(num2) + " = " + to_string(divide(num1, num2));
                    cout << result << endl;
                    history.push_back(result);
                }
                break;
            case '5':
                if (static_cast<int>(num2) != 0) {
                    result = to_string(static_cast<int>(num1)) + " % " + to_string(static_cast<int>(num2)) + " = " + to_string(mod(static_cast<int>(num1), static_cast<int>(num2)));
                    cout << result << endl;
                    history.push_back(result);
                }
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    cout << "Thank you for using the Advanced Calculator. Goodbye!\n";
    return 0;
}
