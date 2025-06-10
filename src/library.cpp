// ===== library.cpp =====
#include "../include/library.h"
#include "../include/io.h"
#include <iostream>
#include <algorithm>

Library::Library() {
    // Không cần tham số filename nữa vì đã chuyển sang class IO
}

void Library::addBook(const BorrowableBook& book) {
    books.push_back(book);
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "No books in the library.\n";
        return;
    }
    
    for (const auto& book : books) {
        book.display();
        std::cout << "===================\n";
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
            return book.returnBook(bookId, returnDate);
        }
    }
    return false;
}

const std::vector<BorrowableBook>& Library::getAllBooks() const {
    return books;
}
