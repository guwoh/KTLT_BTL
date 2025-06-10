// ===== library.cpp =====
#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Library::Library(const std::string& filename) : dataFile(filename) {
    loadFromFile();
}

void Library::addBook(const BorrowableBook& book) {
    books.push_back(book);
    saveToFile();
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
            if (book.borrowBook(borrowerName, borrowDate)) {
                saveToFile();
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Library::returnBook(int bookId, const std::string& returnDate) {
    for (auto& book : books) {
        if (book.getId() == bookId) {
            if (book.returnBook(bookId, returnDate)) {
                saveToFile();
                return true;
            }
            return false;
        }
    }
    return false;
}

void Library::saveToFile() const {
    std::ofstream out(dataFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for writing: " << dataFile << std::endl;
        return;
    }
    
    size_t numBooks = books.size();
    out.write(reinterpret_cast<const char*>(&numBooks), sizeof(numBooks));
    
    for (const auto& book : books) {
        book.writeBinary(out);
    }
}

void Library::loadFromFile() {
    std::ifstream in(dataFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening file for reading: " << dataFile << std::endl;
        return;
    }
    
    size_t numBooks;
    in.read(reinterpret_cast<char*>(&numBooks), sizeof(numBooks));
    
    books.clear();
    for (size_t i = 0; i < numBooks; ++i) {
        books.push_back(BorrowableBook::readBinary(in));
    }
}
