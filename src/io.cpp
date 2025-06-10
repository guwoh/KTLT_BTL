#include "../include/io.h"
#include <fstream>
#include <iostream>
#include <iomanip>

// Định nghĩa các hằng số
const std::string IO::BOOK_BIN_FILE = "data/bin/book.bin";
const std::string IO::SLIP_BIN_FILE = "data/bin/borrowSlip.bin";
const std::string IO::BOOK_TXT_FILE = "data/txt/book.txt";
const std::string IO::SLIP_TXT_FILE = "data/txt/borrowSlip.txt";

void IO::loadData(Library& library, std::vector<BorrowSlip>& slips) {
    // Đọc sách
    std::ifstream bookIn(BOOK_BIN_FILE, std::ios::binary);
    if (bookIn) {
        size_t numBooks;
        bookIn.read(reinterpret_cast<char*>(&numBooks), sizeof(numBooks));
        for (size_t i = 0; i < numBooks; ++i) {
            BorrowableBook book = BorrowableBook::readBinary(bookIn);
            library.addBook(book);
        }
    } else {
        std::cerr << "Không tìm thấy file sách.\n";
    }

    // Đọc phiếu mượn
    std::ifstream slipIn(SLIP_BIN_FILE, std::ios::binary);
    if (slipIn) {
        size_t numSlips;
        slipIn.read(reinterpret_cast<char*>(&numSlips), sizeof(numSlips));
        slips.clear();
        for (size_t i = 0; i < numSlips; ++i) {
            BorrowSlip slip = BorrowSlip::readBinary(slipIn);
            slips.push_back(slip);
        }
    } else {
        std::cerr << "Không tìm thấy file phiếu mượn.\n";
    }
}

void IO::saveData(const Library& library, const std::vector<BorrowSlip>& slips) {
    // Lưu sách
    std::ofstream bookOut(BOOK_BIN_FILE, std::ios::binary);
    if (bookOut) {
        const auto& books = library.getAllBooks();
        size_t numBooks = books.size();
        bookOut.write(reinterpret_cast<const char*>(&numBooks), sizeof(numBooks));
        for (const auto& book : books) {
            book.writeBinary(bookOut);
        }
    } else {
        std::cerr << "Lỗi khi ghi file sách.\n";
    }

    // Lưu phiếu mượn
    std::ofstream slipOut(SLIP_BIN_FILE, std::ios::binary);
    if (slipOut) {
        size_t numSlips = slips.size();
        slipOut.write(reinterpret_cast<const char*>(&numSlips), sizeof(numSlips));
        for (const auto& slip : slips) {
            slip.writeBinary(slipOut);
        }
    } else {
        std::cerr << "Lỗi khi ghi file phiếu mượn.\n";
    }

    // Xuất file text để dễ xem
    exportToText(library, slips);
}

void IO::exportToText(const Library& library, const std::vector<BorrowSlip>& slips) {
    // Xuất sách ra file text
    std::ofstream bookTxt(BOOK_TXT_FILE);
    if (bookTxt) {
        bookTxt << "=== DANH SÁCH SÁCH ===\n\n";
        const auto& books = library.getAllBooks();
        for (const auto& book : books) {
            bookTxt << "ID: " << book.getId() << "\n";
            bookTxt << "Tiêu đề: " << book.getTitle() << "\n";
            bookTxt << "Tác giả: " << book.getAuthor() << "\n";
            bookTxt << "Trạng thái: " << (book.isAvailable() ? "Có sẵn" : "Đã mượn") << "\n";
            if (!book.isAvailable()) {
                bookTxt << "Người mượn: " << book.getBorrower() << "\n";
                bookTxt << "Ngày mượn: " << book.getBorrowDate() << "\n";
            }
            bookTxt << "-------------------\n";
        }
    }

    // Xuất phiếu mượn ra file text
    std::ofstream slipTxt(SLIP_TXT_FILE);
    if (slipTxt) {
        slipTxt << "=== DANH SÁCH PHIẾU MƯỢN ===\n\n";
        for (const auto& slip : slips) {
            slipTxt << "Mã phiếu: " << slip.getId() << "\n";
            slipTxt << "Mã sách: " << slip.getBookId() << "\n";
            slipTxt << "Người mượn: " << slip.getBorrowerName() << "\n";
            slipTxt << "Ngày mượn: " << slip.getBorrowDate() << "\n";
            slipTxt << "Ngày trả: " << (slip.getReturnDate().empty() ? "Chưa trả" : slip.getReturnDate()) << "\n";
            slipTxt << "-------------------\n";
        }
    }
} 