#include "../include/borrowSlip.h"
#include <fstream>
#include <iostream>

BorrowSlip::BorrowSlip(int bookId, const std::string& name, const std::string& bDate, const std::string& rDate)
    : bookId(bookId), borrowerName(name), borrowDate(bDate), returnDate(rDate) {}

BorrowSlip::BorrowSlip(int bookId, const std::string& name, const std::string& bDate)
    : bookId(bookId), borrowerName(name), borrowDate(bDate), returnDate("N/A") {}

void BorrowSlip::returnBook(const std::string& rDate) {
    returnDate = rDate;
}

void BorrowSlip::display() const {
    std::cout << "Book ID: " << bookId << ", Borrower: " << borrowerName
              << ", Borrowed: " << borrowDate << ", Returned: " << returnDate << "\n";
}

std::string BorrowSlip::toText() const {
    return std::to_string(bookId) + "," + borrowerName + "," + borrowDate + "," + returnDate;
}

void BorrowSlip::writeBinary(std::ofstream& out) const {
    size_t nameLen = borrowerName.size();
    size_t bLen = borrowDate.size();
    size_t rLen = returnDate.size();

    out.write((char*)&bookId, sizeof(bookId));
    out.write((char*)&nameLen, sizeof(nameLen));
    out.write(borrowerName.c_str(), nameLen);
    out.write((char*)&bLen, sizeof(bLen));
    out.write(borrowDate.c_str(), bLen);
    out.write((char*)&rLen, sizeof(rLen));
    out.write(returnDate.c_str(), rLen);
}

BorrowSlip BorrowSlip::readBinary(std::ifstream& in) {
    int id;
    size_t len;
    std::string name, bDate, rDate;

    in.read((char*)&id, sizeof(id));

    in.read((char*)&len, sizeof(len));
    name.resize(len);
    in.read(&name[0], len);

    in.read((char*)&len, sizeof(len));
    bDate.resize(len);
    in.read(&bDate[0], len);

    in.read((char*)&len, sizeof(len));
    rDate.resize(len);
    in.read(&rDate[0], len);

    return BorrowSlip(id, name, bDate, rDate);
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
