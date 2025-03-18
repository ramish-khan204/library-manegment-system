#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

struct Borrower {
    int id;
    string name;
    string contact;
};

struct Transaction {
    int borrowerID;
    int bookID;
    string borrowDate;
    string returnDate;
    bool returned;
};
void loadBooksFromFile(vector<Book>& books) {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << "No existing data found. Starting fresh.\n";
        return;
    }

    books.clear();
    Book book;
    while (inFile >> book.id) {
        inFile.ignore();
        getline(inFile, book.title);
        getline(inFile, book.author);
        books.push_back(book);
    }
    inFile.close();
}

void saveBooksToFile(const vector<Book>& books) {
    ofstream outFile("books.txt");
    if (!outFile) {
        cout << "Error: Unable to save data to file.\n";
        return;
    }

    for (const auto& book : books) {
        outFile << book.id << endl;
        outFile << book.title << endl;
        outFile << book.author << endl;
    }
    outFile.close();
}

void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books in the library.\n";
        return;
    }

    cout << "\nList of Books:\n";
    for (const auto& book : books) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << endl;
    }
}

void addBook(vector<Book>& books) {
    Book newBook;
    cout << "Enter book ID: ";
    while (!(cin >> newBook.id)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid numeric book ID: ";
    }
    cin.ignore();
    cout << "Enter book title: ";
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    books.push_back(newBook);
    saveBooksToFile(books);
    cout << "Book added successfully!\n";
}

void deleteBook(vector<Book>& books, int bookID) {
    auto it = remove_if(books.begin(), books.end(), [bookID](const Book& b) { return b.id == bookID; });
    if (it != books.end()) {
        books.erase(it, books.end());
        saveBooksToFile(books);
        cout << "Book deleted successfully!\n";
    } else {
        cout << "Book not found.\n";
    }
}

void addBorrower(vector<Borrower>& borrowers) {
    Borrower newBorrower;
    cout << "Enter borrower ID: ";
    while (!(cin >> newBorrower.id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid numeric borrower ID: ";
    }
    cin.ignore();
    cout << "Enter borrower name: ";
    getline(cin, newBorrower.name);
    cout << "Enter borrower contact: ";
    getline(cin, newBorrower.contact);
    borrowers.push_back(newBorrower);
    cout << "Borrower added successfully!\n";
}

void displayBorrowers(const vector<Borrower>& borrowers) {
    if (borrowers.empty()) {
        cout << "No borrowers in the system.\n";
        return;
    }

    cout << "\nList of Borrowers:\n";
    for (const auto& borrower : borrowers) {
        cout << "ID: " << borrower.id << ", Name: " << borrower.name << ", Contact: " << borrower.contact << endl;
    }
}

int getValidatedChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Please enter a valid option: ";
    }
    return choice;
}

int main() {
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

    loadBooksFromFile(books);

    cout << "Welcome to the Library Management System!\n";

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Delete Book\n";
        cout << "4. Add Borrower\n";
        cout << "5. View Borrowers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedChoice();

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                displayBooks(books);
                break;
            case 3: {
                int bookID;
                cout << "Enter the book ID to delete: ";
                bookID = getValidatedChoice();
                deleteBook(books, bookID);
                break;
            }
            case 4:
                addBorrower(borrowers);
                break;
            case 5:
                displayBorrowers(borrowers);
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

