#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    int copies;

    Book(string t, string a, string i, int c) : title(t), author(a), isbn(i), copies(c) {}
};

class User {
public:
    string name;
    vector<string> borrowedBooks;

    User(string n) : name(n) {}
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook() {
        string title, author, isbn;
        int copies;
        cout << "Enter the title of the book: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the author of the book: ";
        getline(cin, author);
        cout << "Enter the ISBN of the book: ";
        getline(cin, isbn);
        cout << "Enter the number of copies: ";
        cin >> copies;

        Book newBook(title, author, isbn, copies);
        books.push_back(newBook);
        cout << "Book added successfully!\n";
    }

    void updateBook() {
        string isbn;
        cout << "Enter the ISBN of the book to update: ";
        cin.ignore();
        getline(cin, isbn);

        auto it = find_if(books.begin(), books.end(), [&](Book &book) {
            return book.isbn == isbn;
        });

        if (it != books.end()) {
            cout << "Enter new title: ";
            getline(cin, it->title);
            cout << "Enter new author: ";
            getline(cin, it->author);
            cout << "Enter new number of copies: ";
            cin >> it->copies;
            cout << "Book information updated successfully!\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void deleteBook() {
        string isbn;
        cout << "Enter the ISBN of the book to delete: ";
        cin.ignore();
        getline(cin, isbn);

        auto it = remove_if(books.begin(), books.end(), [&](Book &book) {
            return book.isbn == isbn;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book deleted successfully!\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        for (size_t i = 0; i < books.size(); ++i) {
            cout << "Book " << i + 1 << ":\n";
            cout << "Title: " << books[i].title << "\n";
            cout << "Author: " << books[i].author << "\n";
            cout << "ISBN: " << books[i].isbn << "\n";
            cout << "Copies: " << books[i].copies << "\n\n";
        }
    }

    void searchByTitle() {
        string title;
        cout << "Enter the title of the book to search: ";
        cin.ignore();
        getline(cin, title);

        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "Book found:\n";
                cout << "Title: " << book.title << "\n";
                cout << "Author: " << book.author << "\n";
                cout << "ISBN: " << book.isbn << "\n";
                cout << "Copies: " << book.copies << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }
    }

    void searchByAuthor() {
        string author;
        cout << "Enter the author of the book to search: ";
        cin.ignore();
        getline(cin, author);

        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                cout << "Book found:\n";
                cout << "Title: " << book.title << "\n";
                cout << "Author: " << book.author << "\n";
                cout << "ISBN: " << book.isbn << "\n";
                cout << "Copies: " << book.copies << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }
    }

    void addUser() {
        string name;
        cout << "Enter the name of the user: ";
        cin.ignore();
        getline(cin, name);

        User newUser(name);
        users.push_back(newUser);
        cout << "User added successfully!\n";
    }

    void borrowBook() {
        string userName, isbn;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, userName);

        auto userIt = find_if(users.begin(), users.end(), [&](User &user) {
            return user.name == userName;
        });

        if (userIt != users.end()) {
            cout << "Enter the ISBN of the book to borrow: ";
            getline(cin, isbn);

            auto bookIt = find_if(books.begin(), books.end(), [&](Book &book) {
                return book.isbn == isbn;
            });

            if (bookIt != books.end() && bookIt->copies > 0) {
                userIt->borrowedBooks.push_back(isbn);
                bookIt->copies--;
                cout << "Book borrowed successfully!\n";
            } else {
                cout << "Book not available.\n";
            }
        } else {
            cout << "User not found.\n";
        }
    }

    void returnBook() {
        string userName, isbn;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, userName);

        auto userIt = find_if(users.begin(), users.end(), [&](User &user) {
            return user.name == userName;
        });

        if (userIt != users.end()) {
            cout << "Enter the ISBN of the book to return: ";
            getline(cin, isbn);

            auto bookIt = find_if(books.begin(), books.end(), [&](Book &book) {
                return book.isbn == isbn;
            });

            auto borrowedBookIt = find(userIt->borrowedBooks.begin(), userIt->borrowedBooks.end(), isbn);

            if (borrowedBookIt != userIt->borrowedBooks.end()) {
                userIt->borrowedBooks.erase(borrowedBookIt);
                bookIt->copies++;
                cout << "Book returned successfully!\n";
            } else {
                cout << "Book not borrowed by user.\n";
            }
        } else {
            cout << "User not found.\n";
        }
    }

    void displayUsers() {
        if (users.empty()) {
            cout << "No users in the library.\n";
            return;
        }
        for (size_t i = 0; i < users.size(); ++i) {
            cout << "User " << i + 1 << ":\n";
            cout << "Name: " << users[i].name << "\n";
            if (users[i].borrowedBooks.empty()) {
                cout << "No borrowed books.\n";
            } else {
                cout << "Borrowed books:\n";
                for (const auto& isbn : users[i].borrowedBooks) {
                    cout << isbn << "\n";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    Library library;
    bool continueProgram = true;

    while (continueProgram) {
        int choice;
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Update Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Display All Books\n";
        cout << "5. Search Book by Title\n";
        cout << "6. Search Book by Author\n";
        cout << "7. Add User\n";
        cout << "8. Borrow Book\n";
        cout << "9. Return Book\n";
        cout << "10. Display All Users\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.updateBook();
                break;
            case 3:
                library.deleteBook();
                break;
            case 4:
                library.displayBooks();
                break;
            case 5:
                library.searchByTitle();
                break;
            case 6:
                library.searchByAuthor();
                break;
            case 7:
                library.addUser();
                break;
            case 8:
                library.borrowBook();
                break;
            case 9:
                library.returnBook();
                break;
            case 10:
                library.displayUsers();
                break;
            case 11:
                continueProgram = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    cout << "Thank you for using the Library Management System. Goodbye!\n";
    return 0;
}
