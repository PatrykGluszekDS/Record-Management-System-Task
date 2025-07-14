#include "BookRepository.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <optional>

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


std::optional<Book> BookRepository::findById(int id) const {
    std::ifstream ifs(filename_);
    if (!ifs) return std::nullopt;

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        Book b = Book::fromCsv(line);
        if (b.getId() == id)            // match!
            return b;
    }
    return std::nullopt;                // not found
}


/* ───────────── helper: overwrite whole file ───────────── */
void BookRepository::writeAll(const std::vector<Book>& books) const {
    std::ofstream ofs(filename_, std::ios::trunc);     // overwrite
    if (!ofs) throw std::runtime_error("Cannot open " + filename_ + " for writing");
    for (const auto& b : books) ofs << b.toCsv() << '\n';
}

/* ───────────── update ───────────── */
bool BookRepository::update(const Book& updated) {
    auto books = loadAll();
    bool found = false;
    for (auto& b : books) {
        if (b.getId() == updated.getId()) {
            b = updated;
            found = true;
            break;
        }
    }
    if (found) writeAll(books);
    return found;
}

/* ───────────── delete ───────────── */
bool BookRepository::removeById(int id) {
    auto books = loadAll();
    auto it = std::remove_if(books.begin(), books.end(),
                             [id](const Book& b){ return b.getId() == id; });
    if (it == books.end()) return false;        // nothing removed
    books.erase(it, books.end());
    writeAll(books);
    return true;
}


std::vector<Book> BookRepository::loadAllSortedById(bool asc) const {
    auto v = loadAll();
    std::sort(v.begin(), v.end(), [asc](const Book& a, const Book& b) {
        return asc ? a.getId() < b.getId()
                   : a.getId() > b.getId();
    });
    return v;
}

std::vector<Book> BookRepository::loadAllSortedByTitle(bool asc) const {
    auto v = loadAll();
    std::sort(v.begin(), v.end(), [asc](const Book& a, const Book& b) {
        return asc ? a.getTitle() < b.getTitle()
                   : a.getTitle() > b.getTitle();
    });
    return v;
}

bool BookRepository::exportCopy(const std::string& dest) const {
    namespace fs = std::filesystem;
    std::error_code ec;
    fs::copy_file(filename_, dest,
                  fs::copy_options::overwrite_existing, ec);
    return !ec;
}
