// ===== io.h =====
#ifndef IO_H
#define IO_H

#include "book.h"
#include "borrowSlip.h"
#include <vector>
#include <string>

namespace io {
    void saveBooksToText(const std::vector<Book>& books, const std::string& txtPath);
    void saveBooksToBinary(const std::vector<Book>& books, const std::string& binPath);
    void loadBooksFromBinary(std::vector<Book>& books, const std::string& binPath);

    void saveSlipsToText(const std::vector<BorrowSlip>& slips, const std::string& txtPath);
    void saveSlipsToBinary(const std::vector<BorrowSlip>& slips, const std::string& binPath);
    void loadSlipsFromBinary(std::vector<BorrowSlip>& slips, const std::string& binPath);
}

#endif
