#pragma once
#include "Book.hpp"
#include <vector>
#include <string>
#include <optional>

class BookRepository {
private:
    std::string filename_;

    void writeAll(const std::vector<Book>& books) const;   // helper

public:
    explicit BookRepository(std::string filename = "books.csv")
        : filename_(std::move(filename)) {}

    void save(const Book& book);
    std::vector<Book> loadAll() const;
    std::optional<Book> findById(int id) const;

    bool update(const Book& updated);   // returns true on success
    bool removeById(int id);            // returns true on success
    bool exportCopy(const std::string& destPath) const;

    std::vector<Book> loadAllSortedById(bool ascending = true)  const;
    std::vector<Book> loadAllSortedByTitle(bool ascending = true) const;
};
