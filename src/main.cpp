// ===== main.cpp =====
#include "../include/library.h"
#include <iostream>

using namespace std;

int main() {
    Library lib;
    lib.loadBooks("data/bin/book.bin");
    lib.loadSlips("data/bin/borrowSlip.bin");

    int choice;
    do {
        cout << "\n--- LIBRARY SYSTEM ---\n";
        cout << "1. Add Book\n2. View All\n3. Search by Title\n4. Search by Author\n";
        cout << "5. Borrow Book\n6. Return Book\n7. Save and Exit\n";
        cout << "Choose: "; cin >> choice; cin.ignore();

        if (choice == 1) {
            int id, qty; string title, author;
            cout << "Enter ID: "; cin >> id; cin.ignore();
            cout << "Title: "; getline(cin, title);
            cout << "Author: "; getline(cin, author);
            cout << "Quantity: "; cin >> qty;
            lib.addBook(Book(id, title, author, qty));

        } else if (choice == 2) {
            lib.viewBooks();

        } else if (choice == 3) {
            string keyword; cout << "Title keyword: "; cin.ignore(); getline(cin, keyword);
            lib.searchByTitle(keyword);

        } else if (choice == 4) {
            string keyword; cout << "Author keyword: "; cin.ignore(); getline(cin, keyword);
            lib.searchByAuthor(keyword);

        } else if (choice == 5) {
            int id; string name, date;
            cout << "Enter Book ID: "; cin >> id; cin.ignore();
            cout << "Borrower Name: "; getline(cin, name);
            cout << "Borrow Date (YYYY-MM-DD): "; getline(cin, date);
            lib.borrowBook(id, name, date);

        } else if (choice == 6) {
            int id; string date;
            cout << "Enter Book ID: "; cin >> id; cin.ignore();
            cout << "Return Date (YYYY-MM-DD): "; getline(cin, date);
            lib.returnBook(id, date);
        }

    } while (choice != 7);

    lib.saveBooks("data/txt/book.txt", "data/bin/book.bin");
    lib.saveSlips("data/txt/borrowSlip.txt", "data/bin/borrowSlip.bin");
    cout << "Saved and exited.\n";
    return 0;
}
