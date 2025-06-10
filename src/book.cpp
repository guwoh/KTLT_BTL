#include "../include/book.h"
#include <iostream>

// Constructor
Book::Book(int id, const std::string& title, const std::string& author, int quantity)
    : id(id), title(title), author(author), quantity(quantity) {}

// Getter
int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getQuantity() const { return quantity; }

// Setter
void Book::setQuantity(int newQuantity) { quantity = newQuantity; }

// Display
void Book::display() const {
    std::cout << "ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "Quantity: " << quantity << "\n";
}

// Export to readable text
std::string Book::toText() const {
    return std::to_string(id) + "|" + title + "|" + author + "|" + std::to_string(quantity);
}

// Save to binary file
void Book::writeBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    
    size_t titleLength = title.length();
    out.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
    out.write(title.c_str(), titleLength);
    
    size_t authorLength = author.length();
    out.write(reinterpret_cast<const char*>(&authorLength), sizeof(authorLength));
    out.write(author.c_str(), authorLength);
    
    out.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
}

// Load from binary file
Book Book::readBinary(std::ifstream& in) {
    int id;
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    
    size_t titleLength;
    in.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
    std::string title(titleLength, ' ');
    in.read(&title[0], titleLength);
    
    size_t authorLength;
    in.read(reinterpret_cast<char*>(&authorLength), sizeof(authorLength));
    std::string author(authorLength, ' ');
    in.read(&author[0], authorLength);
    
    int quantity;
    in.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
    
    return Book(id, title, author, quantity);
}
