#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <fstream>

class Book {
protected:
    int id;
    std::string title;
    std::string author;
    int quantity;

public:
    // Constructors
    Book(int id, const std::string& title, const std::string& author, int quantity);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getQuantity() const;
    
    // Setters
    void setQuantity(int newQuantity);
    
    // Display
    virtual void display() const;
    
    // File operations
    virtual std::string toText() const;
    virtual void writeBinary(std::ofstream& out) const;
    static Book readBinary(std::ifstream& in);
};

#endif
