// ===== library.h =====
#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "borrowableBook.h"

class Library {
private:
    std::vector<BorrowableBook> books;
    std::string dataFile;

public:
    // Constructor
    Library(const std::string& filename);
    
    // Book management
    void addBook(const BorrowableBook& book);
    void displayAllBooks() const;
    std::vector<BorrowableBook> searchByTitle(const std::string& title) const;
    std::vector<BorrowableBook> searchByAuthor(const std::string& author) const;
    
    // Borrowing operations
    bool borrowBook(int bookId, const std::string& borrowerName, const std::string& borrowDate);
    bool returnBook(int bookId, const std::string& returnDate);
    
    // File operations
    void saveToFile() const;
    void loadFromFile();
};

#endif