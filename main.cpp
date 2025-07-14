#include <iostream>
#include <vector>
#include <limits>
#include "Book.hpp"
#include "BookRepository.hpp"

void showMenu() {
    std::cout << "\n==== Record Management System ====\n";
    std::cout << "1. Add book\n";
    std::cout << "2. List all books\n";
    std::cout << "3. Search book by ID\n";
    std::cout << "4. Update book by ID\n";
    std::cout << "5. Delete book by ID\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    BookRepository repo;                       // defaults to "books.csv"
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush newline

        switch (choice) {
        case 1: {
                int id, year;
                std::string title, author;

                std::cout << "ID: ";     std::cin >> id;
                std::cin.ignore();
                std::cout << "Title: ";  std::getline(std::cin, title);
                std::cout << "Author: "; std::getline(std::cin, author);
                std::cout << "Year: ";   std::cin >> year;

                Book newBook(id, title, author, year);
                try {
                    repo.save(newBook);                 // ← write to CSV
                    std::cout << "Book saved!\n";
                } catch (const std::exception& ex) {
                    std::cerr << "Error: " << ex.what() << '\n';
                }
                break;

        }
        case 2: {
                auto books = repo.loadAll();            // ← read CSV
                if (books.empty()) {
                    std::cout << "No records yet.\n";
                } else {
                    std::cout << "\n--- All books ---\n";
                    for (const auto& b : books) {
                        std::cout << b.getId()    << " | "
                                  << b.getTitle() << " | "
                                  << b.getAuthor()<< " | "
                                  << b.getYear()  << '\n';
                    }
                }
                break;
        }
        case 3: {
                int id;
                std::cout << "Enter ID to search: ";
                std::cin >> id;

                auto result = repo.findById(id);
                if (result) {
                    const Book& b = *result;
                    std::cout << "Found: " << b.getId() << " | "
                              << b.getTitle() << " | "
                              << b.getAuthor() << " | "
                              << b.getYear() << '\n';
                } else {
                    std::cout << "No book with ID " << id << ".\n";
                }
                break;
        }
            /* ─────────────── case 4 – UPDATE ─────────────── */
        case 4: {
                int id;
                std::cout << "Enter ID to update: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                auto existing = repo.findById(id);
                if (!existing) {
                    std::cout << "No book with ID " << id << ".\n";
                    break;
                }

                Book b = *existing;
                std::string input;

                std::cout << "Current title [" << b.getTitle() << "]: ";
                std::getline(std::cin, input);
                if (!input.empty()) b.setTitle(input);

                std::cout << "Current author [" << b.getAuthor() << "]: ";
                std::getline(std::cin, input);
                if (!input.empty()) b.setAuthor(input);

                std::cout << "Current year [" << b.getYear() << "]: ";
                std::getline(std::cin, input);
                if (!input.empty()) b.setYear(std::stoi(input));

                if (repo.update(b))
                    std::cout << "Book updated.\n";
                else
                    std::cout << "Update failed (unexpected).\n";
                break;
        }
            /* ─────────────── case 5 – DELETE ─────────────── */
        case 5: {
                int id;
                std::cout << "Enter ID to delete: ";
                std::cin >> id;

                if (repo.removeById(id))
                    std::cout << "Book deleted.\n";
                else
                    std::cout << "No book with ID " << id << ".\n";
                break;
        }
        case 0:
            std::cout << "Good-bye!\n";
            break;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
