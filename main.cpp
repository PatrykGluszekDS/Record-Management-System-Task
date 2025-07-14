#include <iostream>
#include <vector>
#include "Book.hpp"

void showMenu() {
    std::cout << "\n==== Record Management System ====\n";
    std::cout << "1. Add book\n";
    std::cout << "2. List all books\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    std::vector<Book> books;   // in-memory list for now
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

                books.emplace_back(id, title, author, year);
                std::cout << "Book added!\n";
                break;
        }
        case 2: {
                std::cout << "\n--- All books ---\n";
                for (const auto& b : books) {
                    std::cout << b.getId()   << " | "
                              << b.getTitle() << " | "
                              << b.getAuthor()<< " | "
                              << b.getYear()  << '\n';
                }
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
