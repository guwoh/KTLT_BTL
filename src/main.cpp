// ===== main.cpp =====
#include "../include/library.h"
#include "../include/io.h"
#include <iostream>
#include <vector>
#include <string>

// Hàm nhập số nguyên an toàn
int getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Hàm nhập chuỗi
std::string getString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Hàm nhập ngày
std::string getDate(const std::string& prompt) {
    std::string date;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);
        if (date.length() == 10 && date[4] == '-' && date[7] == '-') {
            return date;
        }
        std::cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
    }
}

// Hàm chọn menu
int getMenuChoice(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n=== " << title << " ===\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ". " << options[i] << "\n";
    }
    std::cout << "0. Exit\n";
    return getInt("Enter your choice: ");
}

void addBook(Library& lib) {
    int id = getInt("Enter book ID: ");
    std::string title = getString("Enter book title: ");
    std::string author = getString("Enter author name: ");
    int quantity = getInt("Enter quantity: ");
    
    BorrowableBook book(id, title, author, quantity);
    lib.addBook(book);
    std::cout << "Book added successfully.\n";
}

void searchBooks(const Library& lib) {
    std::vector<std::string> options = {
        "Search by title",
        "Search by author"
    };
    
    int choice = getMenuChoice("Search Books", options);
    if (choice == 0) return;
    
    std::string searchTerm = getString("Enter search term: ");
    std::vector<BorrowableBook> results;
    
    if (choice == 1) {
        results = lib.searchByTitle(searchTerm);
    } else {
        results = lib.searchByAuthor(searchTerm);
    }
    
    if (results.empty()) {
        std::cout << "No books found.\n";
    } else {
        for (const auto& book : results) {
            book.display();
            std::cout << "-------------------\n";
        }
    }
}

void borrowBook(Library& lib, std::vector<BorrowSlip>& slips) {
    int bookId = getInt("Enter book ID: ");
    std::string borrowerName = getString("Enter borrower name: ");
    std::string borrowDate = getDate("Enter borrow date (YYYY-MM-DD): ");
    
    if (lib.borrowBook(bookId, borrowerName, borrowDate)) {
        slips.emplace_back(bookId, borrowerName, borrowDate);
        std::cout << "Book borrowed successfully.\n";
    } else {
        std::cout << "Failed to borrow book. Book may not exist or be out of stock.\n";
    }
}

void returnBook(Library& lib, std::vector<BorrowSlip>& slips) {
    int bookId = getInt("Enter book ID: ");
    std::string returnDate = getDate("Enter return date (YYYY-MM-DD): ");
    
    if (lib.returnBook(bookId, returnDate)) {
        // Tìm phiếu mượn chưa trả và cập nhật ngày trả
        for (auto& slip : slips) {
            if (slip.getBookId() == bookId && !slip.isBookReturned()) {
                slip.returnBook(returnDate);
                break;
            }
        }
        std::cout << "Book returned successfully.\n";
    } else {
        std::cout << "Failed to return book. Book may not exist or not be borrowed.\n";
    }
}

int main() {
    Library lib;
    std::vector<BorrowSlip> slips;
    IO::loadData(lib, slips);
    std::vector<std::string> mainOptions = {
        "Add new book",
        "View all books",
        "Search books",
        "Borrow a book",
        "Return a book"
    };
    
    while (true) {
        int choice = getMenuChoice("Library Management System", mainOptions);
        
        switch (choice) {
            case 0:
                IO::saveData(lib, slips);
                std::cout << "Goodbye!\n";
                return 0;
            case 1:
                addBook(lib);
                IO::saveData(lib, slips);
                break;
            case 2:
                lib.displayAllBooks();
                break;
            case 3:
                searchBooks(lib);
                break;
            case 4:
                borrowBook(lib, slips);
                IO::saveData(lib, slips);
                break;
            case 5:
                returnBook(lib, slips);
                IO::saveData(lib, slips);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
