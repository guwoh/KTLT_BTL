#ifndef BORROWSLIP_H
#define BORROWSLIP_H

#include <string>

class BorrowSlip {
private:
    int bookId;
    std::string borrowerName;
    std::string borrowDate;
    std::string returnDate;
    bool isReturned;

public:
    // Constructors
    BorrowSlip(int bookId, const std::string& name, const std::string& bDate);
    
    // Operations
    void returnBook(const std::string& rDate);
    bool isBookReturned() const;
    
    // Getters
    int getBookId() const;
    std::string getBorrowerName() const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const;
    
    // Display
    void display() const;
};

#endif
