// cp-1: a library of books, members and loans.
// The Library owns its books and members (composition); a loan refers to them by id (aggregation), so it
// stays valid when the library grows and when the whole library is copied.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

class Library {
public:
    explicit Library(std::size_t loan_limit = 3) : limit_(loan_limit) {}
    int add_book(const std::string& title) {
        books_.push_back(Book{title, -1});
        return static_cast<int>(books_.size()) - 1;
    }
    int add_member(const std::string& name) {
        members_.push_back(name);
        return static_cast<int>(members_.size()) - 1;
    }
    void lend(int book_id, int member_id) {
        check_book(book_id);
        check_member(member_id);
        if (books_[book_id].borrower != -1) throw std::logic_error("book is already lent");
        if (loans_of(member_id) >= limit_) throw std::length_error("loan limit reached");
        books_[book_id].borrower = member_id;
    }
    void give_back(int book_id) {
        check_book(book_id);
        if (books_[book_id].borrower == -1) throw std::logic_error("book is not lent");
        books_[book_id].borrower = -1;
    }
    bool is_lent(int book_id) const {
        check_book(book_id);
        return books_[book_id].borrower != -1;
    }
    std::string borrower_of(int book_id) const {
        check_book(book_id);
        int m = books_[book_id].borrower;
        return m == -1 ? std::string() : members_[m];
    }
    std::vector<std::string> titles_of(int member_id) const {
        check_member(member_id);
        std::vector<std::string> out;
        for (const Book& b : books_)
            out.push_back(b.title);
        return out;
    }
    std::size_t book_count() const { return books_.size(); }
    std::size_t member_count() const { return members_.size(); }
private:
    struct Book {
        std::string title;
        int borrower;                                         // member id, or -1
    };
    void check_book(int id) const { if (id < 0 || id >= static_cast<int>(books_.size())) throw std::out_of_range("unknown book"); }
    void check_member(int id) const { if (id < 0 || id >= static_cast<int>(members_.size())) throw std::out_of_range("unknown member"); }
    std::size_t loans_of(int member_id) const {
        std::size_t n = 0;
        for (const Book& b : books_) if (b.borrower == member_id) ++n;
        return n;
    }
    std::size_t limit_;
    std::vector<Book> books_;
    std::vector<std::string> members_;
};
