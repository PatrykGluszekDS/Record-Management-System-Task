#pragma once
#include <string>

class Book {
private:
    int id_{};                 // unique ID
    std::string title_;
    std::string author_;
    int year_{};

public:
    // ───────────────────────────────── Constructors
    Book() = default;
    Book(int id, std::string title, std::string author, int year);

    // ───────────────────────────────── Getters
    int getId() const        { return id_; }
    const std::string& getTitle()  const { return title_;  }
    const std::string& getAuthor() const { return author_; }
    int getYear() const      { return year_; }

    // ───────────────────────────────── Setters
    void setTitle(const std::string& t)  { title_  = t; }
    void setAuthor(const std::string& a) { author_ = a; }
    void setYear(int y)                  { year_   = y; }

    // ───────────────────────────────── Helpers (for later)
    std::string toCsv() const;           // “id,title,author,year”
    static Book fromCsv(const std::string& line);
};
