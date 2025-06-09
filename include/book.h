#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <fstream>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int quantity;

public:
    // Constructor
    Book(int _id, const std::string& _title, const std::string& _author, int _quantity);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getQuantity() const;

    // Quantity management
    void increaseQuantity();
    bool decreaseQuantity();

    // Display
    void display() const;

    // Export as string
    std::string toText() const;

    // Binary file operations
    void writeBinary(std::ofstream& out) const;
    static Book readBinary(std::ifstream& in);
};

#endif
