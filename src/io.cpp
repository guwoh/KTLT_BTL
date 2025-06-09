// ===== io.cpp =====
#include "../include/io.h"
#include <cstdio> // for FILE*, fopen, fwrite
#include <iostream>

namespace io {

void saveBooksToText(const std::vector<Book>& books, const std::string& txtPath) {
    FILE* f = fopen(txtPath.c_str(), "w");
    if (!f) {
        std::cerr << "Error opening file for writing: " << txtPath << "\n";
        return;
    }
    for (const auto& book : books) {
        std::string line = book.toText() + "\n";
        fwrite(line.c_str(), sizeof(char), line.size(), f);
    }
    fclose(f);
}

void saveBooksToBinary(const std::vector<Book>& books, const std::string& binPath) {
    FILE* f = fopen(binPath.c_str(), "wb");
    if (!f) {
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

        fwrite(&id, sizeof(int), 1, f);
        fwrite(&tLen, sizeof(size_t), 1, f);
        fwrite(title.c_str(), sizeof(char), tLen, f);
        fwrite(&aLen, sizeof(size_t), 1, f);
        fwrite(author.c_str(), sizeof(char), aLen, f);
        fwrite(&qty, sizeof(int), 1, f);
    }
    fclose(f);
}

void saveSlipsToText(const std::vector<BorrowSlip>& slips, const std::string& txtPath) {
    FILE* f = fopen(txtPath.c_str(), "w");
    if (!f) {
        std::cerr << "Error opening file for writing: " << txtPath << "\n";
        return;
    }
    for (const auto& slip : slips) {
        std::string line = slip.toText() + "\n";
        fwrite(line.c_str(), sizeof(char), line.size(), f);
    }
    fclose(f);
}

void saveSlipsToBinary(const std::vector<BorrowSlip>& slips, const std::string& binPath) {
    FILE* f = fopen(binPath.c_str(), "wb");
    if (!f) {
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

        fwrite(&id, sizeof(int), 1, f);
        fwrite(&nLen, sizeof(size_t), 1, f);
        fwrite(name.c_str(), sizeof(char), nLen, f);
        fwrite(&bLen, sizeof(size_t), 1, f);
        fwrite(bDate.c_str(), sizeof(char), bLen, f);
        fwrite(&rLen, sizeof(size_t), 1, f);
        fwrite(rDate.c_str(), sizeof(char), rLen, f);
    }
    fclose(f);
}

} // namespace io
