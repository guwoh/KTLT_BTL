#include "../include/book.h"
#include <iostream>

// Constructor
Book::Book(int id, const std::string& title, const std::string& author, int quantity)
    : id(id), title(title), author(author), quantity(quantity) {}

// Getters
int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getQuantity() const { return quantity; }

// Setters
void Book::setId(int newId) { id = newId; }
void Book::setTitle(const std::string& newTitle) { title = newTitle; }
void Book::setAuthor(const std::string& newAuthor) { author = newAuthor; }
void Book::setQuantity(int newQuantity) { quantity = newQuantity; }

// Display
void Book::display() const {
    std::cout << "ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "Quantity: " << quantity << "\n";
} 