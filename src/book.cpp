#include "../include/book.h"
#include <iostream>

// Constructor
Book::Book(int _id, const std::string& _title, const std::string& _author, int _quantity)
    : id(_id), title(_title), author(_author), quantity(_quantity) {}

// Getter
int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getQuantity() const { return quantity; }

// Increase / Decrease
void Book::increaseQuantity() { quantity++; }
bool Book::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
        return true;
    }
    return false;
}

// Display
void Book::display() const {
    std::cout << "ID: " << id << ", Title: " << title
              << ", Author: " << author << ", Quantity: " << quantity << "\n";
}

// Export to readable text
std::string Book::toText() const {
    return std::to_string(id) + "," + title + "," + author + "," + std::to_string(quantity);
}

// Save to binary file
void Book::writeBinary(std::ofstream& out) const {
    size_t tLen = title.size();
    size_t aLen = author.size();

    out.write((char*)&id, sizeof(id));
    out.write((char*)&tLen, sizeof(tLen));
    out.write(title.c_str(), tLen);
    out.write((char*)&aLen, sizeof(aLen));
    out.write(author.c_str(), aLen);
    out.write((char*)&quantity, sizeof(quantity));
}

// Load from binary file
Book Book::readBinary(std::ifstream& in) {
    int id, quantity;
    size_t len;
    std::string title, author;

    in.read((char*)&id, sizeof(id));

    in.read((char*)&len, sizeof(len));
    title.resize(len);
    in.read(&title[0], len);

    in.read((char*)&len, sizeof(len));
    author.resize(len);
    in.read(&author[0], len);

    in.read((char*)&quantity, sizeof(quantity));

    return Book(id, title, author, quantity);
}
