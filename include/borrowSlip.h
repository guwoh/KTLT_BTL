#ifndef BORROW_SLIP_H
#define BORROW_SLIP_H

#include <string>
#include <fstream>

class BorrowSlip {
private:
    int bookId;
    std::string borrowerName;
    std::string borrowDate;
    std::string returnDate;

public:
    // Constructors
    BorrowSlip(int id, const std::string& name, const std::string& bDate);
    BorrowSlip(int id, const std::string& name, const std::string& bDate, const std::string& rDate);

    // Behavior
    void returnBook(const std::string& rDate);
    void display() const;

    // Export
    std::string toText() const;
    void writeBinary(std::ofstream& out) const;
    static BorrowSlip readBinary(std::ifstream& in);

    // Getter
    int getBookId() const;
    std::string getBorrowerName() const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const;
};

#endif
