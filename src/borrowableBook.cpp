#include "../include/borrowableBook.h"
#include <iostream>

BorrowableBook::BorrowableBook(int id, const std::string& title, const std::string& author, int quantity)
    : Book(id, title, author, quantity) {}

bool BorrowableBook::borrowBook(const std::string& borrowerName, const std::string& borrowDate) {
    if (quantity > 0) {
        quantity--;
        borrowSlips.emplace_back(id, borrowerName, borrowDate);
        return true;
    }
    return false;
}

bool BorrowableBook::returnBook(const std::string& returnDate) {
    for (auto& slip : borrowSlips) {
        if (!slip.isBookReturned()) {
            slip.returnBook(returnDate);
            quantity++;
            return true;
        }
    }
    return false;
}

void BorrowableBook::display() const {
    Book::display();
    std::cout << "Borrow history:\n";
    for (const auto& slip : borrowSlips) {
        slip.display();
    }
}

void BorrowableBook::addBorrowSlip(const BorrowSlip& slip) {
    borrowSlips.push_back(slip);
} 