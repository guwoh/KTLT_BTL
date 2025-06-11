// ===== library.h =====
#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "borrowableBook.h"

class Library {
private:
    std::vector<BorrowableBook> books;

public:
    Library();
    
    void addBook(const BorrowableBook& book);
    void displayAllBooks() const;
    std::vector<BorrowableBook> searchByTitle(const std::string& title) const;
    std::vector<BorrowableBook> searchByAuthor(const std::string& author) const;
    bool borrowBook(int bookId, const std::string& borrowerName, const std::string& borrowDate);
    bool returnBook(int bookId, const std::string& returnDate);
    
    // Thêm các hàm mới
    size_t getBookCount() const { return books.size(); }
    const std::vector<BorrowableBook>& getAllBooks() const { return books; }
};

#endif