// ===== io.h =====
#ifndef IO_H
#define IO_H

#include "book.h"
#include "borrowSlip.h"
#include <vector>
#include <string>
#include <iostream>
#include <limits>

namespace io {
    void saveBooksToText(const std::vector<Book>& books, const std::string& txtPath);
    void saveBooksToBinary(const std::vector<Book>& books, const std::string& binPath);
    void loadBooksFromBinary(std::vector<Book>& books, const std::string& binPath);

    void saveSlipsToText(const std::vector<BorrowSlip>& slips, const std::string& txtPath);
    void saveSlipsToBinary(const std::vector<BorrowSlip>& slips, const std::string& binPath);
    void loadSlipsFromBinary(std::vector<BorrowSlip>& slips, const std::string& binPath);

    // Clear input buffer
    inline void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get integer input with validation
    inline int getInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInputBuffer();
                return value;
            }
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
        }
    }

    // Get string input
    inline std::string getString(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    // Get date input (format: YYYY-MM-DD)
    inline std::string getDate(const std::string& prompt) {
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

    // Display menu and get choice
    inline int getMenuChoice(const std::string& title, const std::vector<std::string>& options) {
        std::cout << "\n=== " << title << " ===\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << (i + 1) << ". " << options[i] << "\n";
        }
        std::cout << "0. Exit\n";
        return getInt("Enter your choice: ");
    }
}

#endif
