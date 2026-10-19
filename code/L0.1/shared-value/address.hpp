// Address is an immutable value: every field is set in the constructor and nothing can change it afterwards.
// A "change" builds a new Address. Two orders can therefore share one Address without either seeing the other's change.
#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class Address {
public:
    Address(std::string street, std::string city) : street_(std::move(street)), city_(std::move(city)) {
        if (street_.empty() || city_.empty()) throw std::invalid_argument("street and city must not be empty");
    }
    const std::string& street() const { return street_; }
    const std::string& city() const { return city_; }
    Address with_street(std::string street) const { return Address(std::move(street), city_); }   // new value, this one is untouched
    bool operator==(const Address&) const = default;
private:
    const std::string street_;
    const std::string city_;
};

class Order {
public:
    explicit Order(std::shared_ptr<const Address> a) : address_(std::move(a)) {}
    const Address& address() const { return *address_; }
    void change_address(std::shared_ptr<const Address> a) { address_ = std::move(a); }   // replaces the whole value
    const Address* address_identity() const { return address_.get(); }
private:
    std::shared_ptr<const Address> address_;
};
