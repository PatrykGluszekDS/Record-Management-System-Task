#pragma once
#include "Book.hpp"
#include <vector>
#include <string>

class BookRepository {
private:
    std::string filename_;            // e.g. "books.csv"

public:
    explicit BookRepository(std::string filename = "books.csv")
        : filename_(std::move(filename)) {}

    void save(const Book& book);              // append one book
    std::vector<Book> loadAll() const;        // read entire file
};
