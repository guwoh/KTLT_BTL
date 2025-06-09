// ===== library.cpp =====
#include "../include/library.h"
#include <iostream>
#include <fstream>

// === Book functions ===
void Library::loadBooks(const std::string& binPath) {
    books.clear();
    std::ifstream bin(binPath, std::ios::binary);
    while (bin.peek() != EOF) {
        books.push_back(Book::readBinary(bin));
    }
    bin.close();
}

void Library::saveBooks(const std::string& txtPath, const std::string& binPath) const {
    std::ofstream txt(txtPath);
    std::ofstream bin(binPath, std::ios::binary);
    for (const auto& b : books) {
        txt << b.toText() << "\n";
        b.writeBinary(bin);
    }
    txt.close();
    bin.close();
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::viewBooks() const {
    for (const auto& b : books) b.display();
}

void Library::searchByTitle(const std::string& title) const {
    for (const auto& b : books) {
        if (b.getTitle().find(title) != std::string::npos) {
            b.display();
        }
    }
}

void Library::searchByAuthor(const std::string& author) const {
    for (const auto& b : books) {
        if (b.getAuthor().find(author) != std::string::npos) {
            b.display();
        }
    }
}

// === BorrowSlip functions ===
void Library::loadSlips(const std::string& binPath) {
    slips.clear();
    std::ifstream bin(binPath, std::ios::binary);
    while (bin.peek() != EOF) {
        slips.push_back(BorrowSlip::readBinary(bin));
    }
    bin.close();
}

void Library::saveSlips(const std::string& txtPath, const std::string& binPath) const {
    std::ofstream txt(txtPath);
    std::ofstream bin(binPath, std::ios::binary);
    for (const auto& s : slips) {
        txt << s.toText() << "\n";
        s.writeBinary(bin);
    }
    txt.close();
    bin.close();
}

void Library::borrowBook(int bookId, const std::string& name, const std::string& borrowDate) {
    for (auto& b : books) {
        if (b.getId() == bookId) {
            if (b.decreaseQuantity()) {
                slips.emplace_back(bookId, name, borrowDate, "");
                std::cout << "Borrowed successfully.\n";
            } else {
                std::cout << "Book out of stock.\n";
            }
            return;
        }
    }
    std::cout << "Book not found.\n";
}

void Library::returnBook(int bookId, const std::string& returnDate) {
    for (auto& slip : slips) {
        if (slip.toText().find(std::to_string(bookId)) != std::string::npos && slip.toText().find(",,") != std::string::npos) {
            slip = BorrowSlip(bookId, slip.toText().substr(2, slip.toText().find(",", 2)), slip.toText().substr(slip.toText().find(",", 2) + 1, 10), returnDate);
            break;
        }
    }
    for (auto& b : books) {
        if (b.getId() == bookId) {
            b.increaseQuantity();
            break;
        }
    }
    std::cout << "Returned successfully.\n";
}
