#include "Book.hpp"
#include <sstream>

Book::Book(int id, std::string title, std::string author, int year)
        : id_(id), title_(std::move(title)), author_(std::move(author)), year_(year) {}

std::string Book::toCsv() const {
    std::ostringstream oss;
    oss << id_ << ',' << title_ << ',' << author_ << ',' << year_;
    return oss.str();
}

Book Book::fromCsv(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    std::getline(iss, token, ',');  int id = std::stoi(token);
    std::getline(iss, token, ',');  std::string title = token;
    std::getline(iss, token, ',');  std::string author = token;
    std::getline(iss, token, ',');  int year = std::stoi(token);

    return {id, title, author, year};
}
