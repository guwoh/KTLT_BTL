// ===== library.cpp =====
#include "../include/library.h"
#include <iostream>
#include <algorithm>

Library::Library() {}

void Library::addBook(const BorrowableBook& book) {
    books.push_back(book);
}

void Library::displayAllBooks() const {
    for (const auto& book : books) {
        book.display();
        std::cout << "-------------------\n";
    }
}

std::vector<BorrowableBook> Library::searchByTitle(const std::string& title) const {
    std::vector<BorrowableBook> results;
    for (const auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

std::vector<BorrowableBook> Library::searchByAuthor(const std::string& author) const {
    std::vector<BorrowableBook> results;
    for (const auto& book : books) {
        if (book.getAuthor().find(author) != std::string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

bool Library::borrowBook(int bookId, const std::string& borrowerName, const std::string& borrowDate) {
    for (auto& book : books) {
        if (book.getId() == bookId) {
            return book.borrowBook(borrowerName, borrowDate);
        }
    }
    return false;
}

bool Library::returnBook(int bookId, const std::string& returnDate) {
    for (auto& book : books) {
        if (book.getId() == bookId) {
            return book.returnBook(returnDate);
        }
    }
    return false;
}
