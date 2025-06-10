#include "../include/borrowSlip.h"
#include <fstream>
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

std::string BorrowSlip::toText() const {
    return std::to_string(bookId) + "|" + borrowerName + "|" + borrowDate + "|" + 
           (isReturned ? returnDate : "Not Returned");
}

void BorrowSlip::writeBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&bookId), sizeof(bookId));
    
    size_t nameLength = borrowerName.length();
    out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    out.write(borrowerName.c_str(), nameLength);
    
    size_t borrowDateLength = borrowDate.length();
    out.write(reinterpret_cast<const char*>(&borrowDateLength), sizeof(borrowDateLength));
    out.write(borrowDate.c_str(), borrowDateLength);
    
    out.write(reinterpret_cast<const char*>(&isReturned), sizeof(isReturned));
    
    if (isReturned) {
        size_t returnDateLength = returnDate.length();
        out.write(reinterpret_cast<const char*>(&returnDateLength), sizeof(returnDateLength));
        out.write(returnDate.c_str(), returnDateLength);
    }
}

BorrowSlip BorrowSlip::readBinary(std::ifstream& in) {
    int bookId;
    in.read(reinterpret_cast<char*>(&bookId), sizeof(bookId));
    
    size_t nameLength;
    in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    std::string borrowerName(nameLength, ' ');
    in.read(&borrowerName[0], nameLength);
    
    size_t borrowDateLength;
    in.read(reinterpret_cast<char*>(&borrowDateLength), sizeof(borrowDateLength));
    std::string borrowDate(borrowDateLength, ' ');
    in.read(&borrowDate[0], borrowDateLength);
    
    bool isReturned;
    in.read(reinterpret_cast<char*>(&isReturned), sizeof(isReturned));
    
    BorrowSlip slip(bookId, borrowerName, borrowDate);
    if (isReturned) {
        size_t returnDateLength;
        in.read(reinterpret_cast<char*>(&returnDateLength), sizeof(returnDateLength));
        std::string returnDate(returnDateLength, ' ');
        in.read(&returnDate[0], returnDateLength);
        slip.returnBook(returnDate);
    }
    
    return slip;
}

int BorrowSlip::getBookId() const {
    return bookId;
}

int BorrowSlip::getId() const {
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
