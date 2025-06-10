// ===== main.cpp =====
#include "../include/library.h"
#include "../include/io.h"
#include <iostream>
#include <vector>

void addBook(Library& lib) {
    int id = io::getInt("Enter book ID: ");
    std::string title = io::getString("Enter book title: ");
    std::string author = io::getString("Enter author name: ");
    int quantity = io::getInt("Enter quantity: ");
    
    BorrowableBook book(id, title, author, quantity);
    lib.addBook(book);
    std::cout << "Book added successfully.\n";
}

void searchBooks(const Library& lib) {
    std::vector<std::string> options = {
        "Search by title",
        "Search by author"
    };
    
    int choice = io::getMenuChoice("Search Books", options);
    if (choice == 0) return;
    
    std::string searchTerm = io::getString("Enter search term: ");
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

void borrowBook(Library& lib) {
    int bookId = io::getInt("Enter book ID: ");
    std::string borrowerName = io::getString("Enter borrower name: ");
    std::string borrowDate = io::getDate("Enter borrow date (YYYY-MM-DD): ");
    
    if (lib.borrowBook(bookId, borrowerName, borrowDate)) {
        std::cout << "Book borrowed successfully.\n";
    } else {
        std::cout << "Failed to borrow book. Book may not exist or be out of stock.\n";
    }
}

void returnBook(Library& lib) {
    int bookId = io::getInt("Enter book ID: ");
    std::string returnDate = io::getDate("Enter return date (YYYY-MM-DD): ");
    
    if (lib.returnBook(bookId, returnDate)) {
        std::cout << "Book returned successfully.\n";
    } else {
        std::cout << "Failed to return book. Book may not exist or not be borrowed.\n";
    }
}

int main() {
    Library lib("library.dat");
    std::vector<std::string> mainOptions = {
        "Add new book",
        "View all books",
        "Search books",
        "Borrow a book",
        "Return a book"
    };
    
    while (true) {
        int choice = io::getMenuChoice("Library Management System", mainOptions);
        
        switch (choice) {
            case 0:
                std::cout << "Goodbye!\n";
                return 0;
            case 1:
                addBook(lib);
                break;
            case 2:
                lib.displayAllBooks();
                break;
            case 3:
                searchBooks(lib);
                break;
            case 4:
                borrowBook(lib);
                break;
            case 5:
                returnBook(lib);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
