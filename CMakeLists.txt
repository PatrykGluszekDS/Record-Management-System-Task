cmake_minimum_required(VERSION 3.31)
project(Internship)

set(CMAKE_CXX_STANDARD 23)

add_executable(Internship main.cpp
        Book.cpp
        Book.hpp
        BookRepository.cpp
        BookRepository.hpp)
