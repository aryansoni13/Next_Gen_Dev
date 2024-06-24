#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>   
#include <iomanip>  

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    bool guessedCorrectly = false;

    cout << "Welcome to the Number Guessing Game!\n";
    cout << "I have selected a number between 1 and 100.\n";
    cout << "You need to guess what it is.\n";
    cout << "You will be given feedback after each guess.\n\n";

    do {
        cout << "Enter your guess: ";
        while (!(cin >> guess)) {
            cout << "Invalid input. Please enter a valid number between 1 and 100.\n";
            clearInputBuffer();
            cout << "Enter your guess: ";
        }
        attempts++;

        if (guess < 1 || guess > 100) {
            cout << "Out of range! Please enter a number between 1 and 100.\n";
        } else if (guess < secretNumber) {
            cout << "Too low! Try again.\n";
        } else if (guess > secretNumber) {
            cout << "Too high! Try again.\n";
        } else {
            guessedCorrectly = true;
            cout << "\nCongratulations! You guessed the number " << secretNumber << " in " << attempts << " attempts!\n";
        }
    } while (!guessedCorrectly);

    
    if (attempts == 1) {
        cout << "Wow! You got it on your first try! You're a mind reader!\n";
    } else if (attempts <= 5) {
        cout << "Well done! You guessed it in " << attempts << " attempts. That's impressive!\n";
    } else if (attempts <= 10) {
        cout << "Good job! You guessed it in " << attempts << " attempts.\n";
    } else {
        cout << "Finally! You guessed it in " << attempts << " attempts. Keep practicing!\n";
    }

    return 0;
}
