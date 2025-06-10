#include "../include/borrowableBook.h"
#include <iostream>

BorrowableBook::BorrowableBook(int id, const std::string& title, const std::string& author, int quantity)
    : Book(id, title, author, quantity) {}

bool BorrowableBook::borrowBook(const std::string& borrowerName, const std::string& borrowDate) {
    if (getQuantity() > 0) {
        borrowSlips.emplace_back(getId(), borrowerName, borrowDate);
        setQuantity(getQuantity() - 1);
        return true;
    }
    return false;
}

bool BorrowableBook::returnBook(int bookId, const std::string& returnDate) {
    for (auto& slip : borrowSlips) {
        if (slip.getBookId() == bookId && !slip.isBookReturned()) {
            slip.returnBook(returnDate);
            setQuantity(getQuantity() + 1);
            return true;
        }
    }
    return false;
}

void BorrowableBook::display() const {
    Book::display();
    std::cout << "Borrow History:\n";
    displayBorrowHistory();
}

void BorrowableBook::displayBorrowHistory() const {
    for (const auto& slip : borrowSlips) {
        slip.display();
        std::cout << "-------------------\n";
    }
}

std::string BorrowableBook::toText() const {
    std::string result = Book::toText() + "\nBorrow History:\n";
    for (const auto& slip : borrowSlips) {
        result += slip.toText() + "\n";
    }
    return result;
}

void BorrowableBook::writeBinary(std::ofstream& out) const {
    Book::writeBinary(out);
    
    size_t numSlips = borrowSlips.size();
    out.write(reinterpret_cast<const char*>(&numSlips), sizeof(numSlips));
    
    for (const auto& slip : borrowSlips) {
        slip.writeBinary(out);
    }
}

BorrowableBook BorrowableBook::readBinary(std::ifstream& in) {
    Book baseBook = Book::readBinary(in);
    BorrowableBook book(baseBook.getId(), baseBook.getTitle(), 
                       baseBook.getAuthor(), baseBook.getQuantity());
    
    size_t numSlips;
    in.read(reinterpret_cast<char*>(&numSlips), sizeof(numSlips));
    
    for (size_t i = 0; i < numSlips; ++i) {
        book.borrowSlips.push_back(BorrowSlip::readBinary(in));
    }
    
    return book;
} 