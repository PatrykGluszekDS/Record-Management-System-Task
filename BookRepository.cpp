#include "BookRepository.hpp"
#include <fstream>

void BookRepository::save(const Book& book) {
    std::ofstream ofs(filename_, std::ios::app);  // append mode
    if (!ofs) throw std::runtime_error("Cannot open " + filename_);
    ofs << book.toCsv() << '\n';
}

std::vector<Book> BookRepository::loadAll() const {
    std::ifstream ifs(filename_);
    if (!ifs) return {};                          // no file yet = empty list

    std::vector<Book> books;
    std::string line;
    while (std::getline(ifs, line)) {
        if (!line.empty())
            books.push_back(Book::fromCsv(line));
    }
    return books;
}
