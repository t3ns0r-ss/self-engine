// cp-1: a library of books, members and loans. Build it in 45 minutes.
// The Library owns its books and members; a loan refers to a book and a member without owning either.
//  add_book(title) and add_member(name) return ids 0, 1, 2, ... in the order added.
//  lend(book, member): std::out_of_range for an unknown id; std::logic_error if the book is already lent;
//    std::length_error if the member already holds loan_limit books (default 3). A refused call changes nothing.
//  give_back(book): std::out_of_range for an unknown id; std::logic_error if the book is not lent.
//  is_lent(book), borrower_of(book) (the member's name, or "" if not lent), titles_of(member) (by book id),
//  book_count(), member_count().
// Copying a Library gives an independent library: lending in the copy does not lend in the original.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

class Library {
public:
    explicit Library(std::size_t loan_limit = 3) { (void)loan_limit; }
    int add_book(const std::string& title) { (void)title; throw std::logic_error("not implemented"); }
    int add_member(const std::string& name) { (void)name; throw std::logic_error("not implemented"); }
    void lend(int book_id, int member_id) { (void)book_id; (void)member_id; throw std::logic_error("not implemented"); }
    void give_back(int book_id) { (void)book_id; throw std::logic_error("not implemented"); }
    bool is_lent(int book_id) const { (void)book_id; throw std::logic_error("not implemented"); }
    std::string borrower_of(int book_id) const { (void)book_id; throw std::logic_error("not implemented"); }
    std::vector<std::string> titles_of(int member_id) const { (void)member_id; throw std::logic_error("not implemented"); }
    std::size_t book_count() const { throw std::logic_error("not implemented"); }
    std::size_t member_count() const { throw std::logic_error("not implemented"); }
};
