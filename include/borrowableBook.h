#ifndef BORROWABLE_BOOK_H
#define BORROWABLE_BOOK_H

#include "book.h"
#include <vector>
#include "borrowSlip.h"

class BorrowableBook : public Book {
private:
    std::vector<BorrowSlip> borrowSlips;

public:
    // Constructor
    BorrowableBook(int id, const std::string& title, const std::string& author, int quantity);
    
    // Borrowing operations
    bool borrowBook(const std::string& borrowerName, const std::string& borrowDate);
    bool returnBook(int bookId, const std::string& returnDate);
    
    // Display
    void display() const override;
    void displayBorrowHistory() const;
    
    // File operations
    std::string toText() const override;
    void writeBinary(std::ofstream& out) const override;
    static BorrowableBook readBinary(std::ifstream& in);
};

#endif 