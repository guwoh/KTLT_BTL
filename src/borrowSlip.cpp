#include "../include/borrowSlip.h"
#include <iostream>

BorrowSlip::BorrowSlip(int bookId, const std::string& name, const std::string& bDate)
    : bookId(bookId), borrowerName(name), borrowDate(bDate), isReturned(false) {}

void BorrowSlip::returnBook(const std::string& rDate) {
    returnDate = rDate;
    isReturned = true;
}

bool BorrowSlip::isBookReturned() const {
    return isReturned;
}

void BorrowSlip::display() const {
    std::cout << "Book ID: " << bookId << "\n"
              << "Borrower: " << borrowerName << "\n"
              << "Borrow Date: " << borrowDate << "\n"
              << "Status: " << (isReturned ? "Returned" : "Not Returned") << "\n";
    if (isReturned) {
        std::cout << "Return Date: " << returnDate << "\n";
    }
}

int BorrowSlip::getBookId() const {
    return bookId;
}

std::string BorrowSlip::getBorrowerName() const {
    return borrowerName;
}

std::string BorrowSlip::getBorrowDate() const {
    return borrowDate;
}

std::string BorrowSlip::getReturnDate() const {
    return returnDate;
}
