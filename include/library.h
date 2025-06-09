// ===== library.h =====
#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include "borrowSlip.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<BorrowSlip> slips;

public:
    // Book management
    void loadBooks(const std::string& binPath);
    void saveBooks(const std::string& txtPath, const std::string& binPath) const;
    void addBook(const Book& book);
    void viewBooks() const;
    void searchByTitle(const std::string& title) const;
    void searchByAuthor(const std::string& author) const;

    // Borrow/Return management
    void loadSlips(const std::string& binPath);
    void saveSlips(const std::string& txtPath, const std::string& binPath) const;
    void borrowBook(int bookId, const std::string& name, const std::string& borrowDate);
    void returnBook(int bookId, const std::string& returnDate);
};

#endif