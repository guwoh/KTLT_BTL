#ifndef BOOK_H
#define BOOK_H

#include <string>
// use for string stream
#include <fstream>
// use for binary file
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
    // set id
    void setId(int newId);
    // set title
    void setTitle(const std::string& newTitle);
    // set author
    void setAuthor(const std::string& newAuthor);
    // set quantity
    void setQuantity(int newQuantity);
    
    // Display
    virtual void display() const;
    
    // File operations
    virtual std::string toText() const;
    // reader and borrow
    virtual void writeBinary(std::ofstream& out) const;
    static Book readBinary(std::ifstream& in);
};

#endif
