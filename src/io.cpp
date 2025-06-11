#include "../include/io.h"
#include "../include/library.h"
#include <stdio.h>
#include <string.h>

namespace IO {
    const char* BOOKS_BIN = "../data/books.bin";
    const char* BOOKS_TXT = "../data/books.txt";
    const char* BORROWERS_TXT = "../data/borrowers.txt";

    bool loadData(Library& lib) {
        // Load books from binary file
        FILE* fp = fopen(BOOKS_BIN, "rb");
        if (!fp) {
            printf("Failed to open books binary file for reading\n");
            return false;
        }

        int count;
        if (fread(&count, sizeof(int), 1, fp) != 1) {
            printf("Failed to read book count\n");
            fclose(fp);
            return false;
        }

        for (int i = 0; i < count; i++) {
            int id;
            int titleLen;
            int authorLen;
            int quantity;
            int borrowSlipCount;

            if (fread(&id, sizeof(int), 1, fp) != 1 ||
                fread(&titleLen, sizeof(int), 1, fp) != 1 ||
                fread(&authorLen, sizeof(int), 1, fp) != 1 ||
                fread(&quantity, sizeof(int), 1, fp) != 1 ||
                fread(&borrowSlipCount, sizeof(int), 1, fp) != 1) {
                printf("Failed to read book data\n");
                fclose(fp);
                return false;
            }

            char* title = new char[titleLen + 1];
            char* author = new char[authorLen + 1];

            if (fread(title, sizeof(char), titleLen, fp) != titleLen ||
                fread(author, sizeof(char), authorLen, fp) != authorLen) {
                printf("Failed to read book strings\n");
                delete[] title;
                delete[] author;
                fclose(fp);
                return false;
            }

            title[titleLen] = '\0';
            author[authorLen] = '\0';

            BorrowableBook book(id, title, author, quantity);
            delete[] title;
            delete[] author;

            for (int j = 0; j < borrowSlipCount; j++) {
                int borrowerNameLen;
                int borrowDateLen;
                int returnDateLen;
                bool isReturned;

                if (fread(&borrowerNameLen, sizeof(int), 1, fp) != 1 ||
                    fread(&borrowDateLen, sizeof(int), 1, fp) != 1 ||
                    fread(&returnDateLen, sizeof(int), 1, fp) != 1 ||
                    fread(&isReturned, sizeof(bool), 1, fp) != 1) {
                    printf("Failed to read borrow slip data\n");
                    fclose(fp);
                    return false;
                }

                char* borrowerName = new char[borrowerNameLen + 1];
                char* borrowDate = new char[borrowDateLen + 1];
                char* returnDate = new char[returnDateLen + 1];

                if (fread(borrowerName, sizeof(char), borrowerNameLen, fp) != borrowerNameLen ||
                    fread(borrowDate, sizeof(char), borrowDateLen, fp) != borrowDateLen ||
                    fread(returnDate, sizeof(char), returnDateLen, fp) != returnDateLen) {
                    printf("Failed to read borrow slip strings\n");
                    delete[] borrowerName;
                    delete[] borrowDate;
                    delete[] returnDate;
                    fclose(fp);
                    return false;
                }

                borrowerName[borrowerNameLen] = '\0';
                borrowDate[borrowDateLen] = '\0';
                returnDate[returnDateLen] = '\0';

                BorrowSlip slip(id, borrowerName, borrowDate);
                if (isReturned) {
                    slip.returnBook(returnDate);
                }
                book.addBorrowSlip(slip);

                delete[] borrowerName;
                delete[] borrowDate;
                delete[] returnDate;
            }

            lib.addBook(book);
        }

        fclose(fp);
        printf("Successfully loaded %d books with their borrow slips\n", count);
        return true;
    }

    bool saveData(const Library& lib) {
        // Save books to binary file
        FILE* fp = fopen(BOOKS_BIN, "wb");
        if (!fp) {
            printf("Failed to open books binary file for writing\n");
            return false;
        }

        int count = lib.getBookCount();
        if (fwrite(&count, sizeof(int), 1, fp) != 1) {
            printf("Failed to write book count\n");
            fclose(fp);
            return false;
        }

        std::vector<BorrowableBook> books = lib.getAllBooks();
        for (const auto& book : books) {
            int id = book.getId();
            const std::string& title = book.getTitle();
            const std::string& author = book.getAuthor();
            int quantity = book.getQuantity();
            int borrowSlipCount = book.getBorrowSlipCount();
            int titleLen = title.length();
            int authorLen = author.length();

            if (fwrite(&id, sizeof(int), 1, fp) != 1 ||
                fwrite(&titleLen, sizeof(int), 1, fp) != 1 ||
                fwrite(&authorLen, sizeof(int), 1, fp) != 1 ||
                fwrite(&quantity, sizeof(int), 1, fp) != 1 ||
                fwrite(&borrowSlipCount, sizeof(int), 1, fp) != 1) {
                printf("Failed to write book data\n");
                fclose(fp);
                return false;
            }

            if (fwrite(title.c_str(), sizeof(char), titleLen, fp) != titleLen ||
                fwrite(author.c_str(), sizeof(char), authorLen, fp) != authorLen) {
                printf("Failed to write book strings\n");
                fclose(fp);
                return false;
            }

            std::vector<BorrowSlip> slips = book.getBorrowSlips();
            for (const auto& slip : slips) {
                const std::string& borrowerName = slip.getBorrowerName();
                const std::string& borrowDate = slip.getBorrowDate();
                const std::string& returnDate = slip.getReturnDate();
                bool isReturned = slip.isBookReturned();
                int borrowerNameLen = borrowerName.length();
                int borrowDateLen = borrowDate.length();
                int returnDateLen = returnDate.length();

                if (fwrite(&borrowerNameLen, sizeof(int), 1, fp) != 1 ||
                    fwrite(&borrowDateLen, sizeof(int), 1, fp) != 1 ||
                    fwrite(&returnDateLen, sizeof(int), 1, fp) != 1 ||
                    fwrite(&isReturned, sizeof(bool), 1, fp) != 1) {
                    printf("Failed to write borrow slip data\n");
                    fclose(fp);
                    return false;
                }

                if (fwrite(borrowerName.c_str(), sizeof(char), borrowerNameLen, fp) != borrowerNameLen ||
                    fwrite(borrowDate.c_str(), sizeof(char), borrowDateLen, fp) != borrowDateLen ||
                    fwrite(returnDate.c_str(), sizeof(char), returnDateLen, fp) != returnDateLen) {
                    printf("Failed to write borrow slip strings\n");
                    fclose(fp);
                    return false;
                }
            }
        }

        fclose(fp);
        printf("Successfully saved %d books with their borrow slips to binary file\n", count);

        // Save to text files
        // Save books to text file
        fp = fopen(BOOKS_TXT, "w");
        if (!fp) {
            printf("Failed to open books text file for writing\n");
            return false;
        }

        fprintf(fp, "=== DANH SACH SACH ===\n");
        for (const auto& book : books) {
            fprintf(fp, "ID: %d\n", book.getId());
            fprintf(fp, "Ten sach: %s\n", book.getTitle().c_str());
            fprintf(fp, "Tac gia: %s\n", book.getAuthor().c_str());
            fprintf(fp, "So luong: %d\n", book.getQuantity());
            fprintf(fp, "-------------------\n");
        }
        fclose(fp);
        printf("Successfully saved books to text file\n");

        // Save borrowers to text file
        fp = fopen(BORROWERS_TXT, "w");
        if (!fp) {
            printf("Failed to open borrowers text file for writing\n");
            return false;
        }

        fprintf(fp, "=== DANH SACH NGUOI MUON ===\n");
        for (const auto& book : books) {
            fprintf(fp, "Sach ID: %d\n", book.getId());
            fprintf(fp, "Ten sach: %s\n", book.getTitle().c_str());
            
            for (const auto& slip : book.getBorrowSlips()) {
                fprintf(fp, "  Nguoi muon: %s\n", slip.getBorrowerName().c_str());
                fprintf(fp, "  Ngay muon: %s\n", slip.getBorrowDate().c_str());
                fprintf(fp, "  Trang thai: %s\n", slip.isBookReturned() ? "Da tra" : "Chua tra");
                if (slip.isBookReturned()) {
                    fprintf(fp, "  Ngay tra: %s\n", slip.getReturnDate().c_str());
                }
                fprintf(fp, "  -------------------\n");
            }
            fprintf(fp, "-------------------\n");
        }
        fclose(fp);
        printf("Successfully saved borrowers to text file\n");

        return true;
    }
} 