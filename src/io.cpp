// ===== io.cpp =====
#include "../include/io.h"
#include <fstream>
#include <iostream>

namespace io {

void saveBooksToText(const std::vector<Book>& books, const std::string& txtPath) {
    std::ofstream outFile(txtPath);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << txtPath << "\n";
        return;
    }
    for (const auto& book : books) {
        outFile << book.toText() << "\n";
    }
    outFile.close();
}

void saveBooksToBinary(const std::vector<Book>& books, const std::string& binPath) {
    std::ofstream outFile(binPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening binary file: " << binPath << "\n";
        return;
    }
    for (const auto& book : books) {
        int id = book.getId();
        int qty = book.getQuantity();
        std::string title = book.getTitle();
        std::string author = book.getAuthor();

        size_t tLen = title.size();
        size_t aLen = author.size();

        outFile.write(reinterpret_cast<const char*>(&id), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&tLen), sizeof(size_t));
        outFile.write(title.c_str(), tLen);
        outFile.write(reinterpret_cast<const char*>(&aLen), sizeof(size_t));
        outFile.write(author.c_str(), aLen);
        outFile.write(reinterpret_cast<const char*>(&qty), sizeof(int));
    }
    outFile.close();
}

void saveSlipsToText(const std::vector<BorrowSlip>& slips, const std::string& txtPath) {
    std::ofstream outFile(txtPath);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << txtPath << "\n";
        return;
    }
    for (const auto& slip : slips) {
        outFile << slip.toText() << "\n";
    }
    outFile.close();
}

void saveSlipsToBinary(const std::vector<BorrowSlip>& slips, const std::string& binPath) {
    std::ofstream outFile(binPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening binary file: " << binPath << "\n";
        return;
    }
    for (const auto& slip : slips) {
        int id = slip.getBookId();
        std::string name = slip.getBorrowerName();
        std::string bDate = slip.getBorrowDate();
        std::string rDate = slip.getReturnDate();

        size_t nLen = name.size();
        size_t bLen = bDate.size();
        size_t rLen = rDate.size();

        outFile.write(reinterpret_cast<const char*>(&id), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&nLen), sizeof(size_t));
        outFile.write(name.c_str(), nLen);
        outFile.write(reinterpret_cast<const char*>(&bLen), sizeof(size_t));
        outFile.write(bDate.c_str(), bLen);
        outFile.write(reinterpret_cast<const char*>(&rLen), sizeof(size_t));
        outFile.write(rDate.c_str(), rLen);
    }
    outFile.close();
}

} // namespace io
