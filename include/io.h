// ===== io.h =====
#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include "library.h"
#include "borrowSlip.h"

class IO {
private:
    static const std::string BOOK_BIN_FILE;
    static const std::string SLIP_BIN_FILE;
    static const std::string BOOK_TXT_FILE;
    static const std::string SLIP_TXT_FILE;

public:
    // Đọc dữ liệu từ 2 file bin khi khởi động chương trình
    static void loadData(Library& library, std::vector<BorrowSlip>& slips);
    
    // Lưu dữ liệu vào 2 file bin sau mỗi thao tác thay đổi
    static void saveData(const Library& library, const std::vector<BorrowSlip>& slips);
    
    // Xuất dữ liệu ra 2 file text để xem (không cần đọc lại)
    static void exportToText(const Library& library, const std::vector<BorrowSlip>& slips);
};

#endif
