// A small online shop. Who owns what is written in the member declarations; diagram.mmd draws the same thing.
#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

inline int live_customers = 0;
inline int live_items = 0;
inline int live_orders = 0;

class Mailer {
public:
    virtual ~Mailer() = default;
    virtual void send(const std::string& to, const std::string& text) = 0;
};

class ConsoleMailer : public Mailer {
public:
    void send(const std::string& to, const std::string& text) override { sent_.push_back(to + ": " + text); }
    std::size_t sent() const { return sent_.size(); }
private:
    std::vector<std::string> sent_;
};

class Customer {
public:
    Customer(std::string name, std::string email) : name_(std::move(name)), email_(std::move(email)) { ++live_customers; }
    ~Customer() { --live_customers; }
    Customer(const Customer&) = delete;
    Customer& operator=(const Customer&) = delete;
    const std::string& email() const { return email_; }
private:
    std::string name_;
    std::string email_;
};

class Item {
public:
    Item(std::string sku, int cents) : sku_(std::move(sku)), cents_(cents) { ++live_items; }
    ~Item() { --live_items; }
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
    const std::string& sku() const { return sku_; }
    int cents() const { return cents_; }
private:
    std::string sku_;
    int cents_;
};

class Catalog {
public:
    const Item& add(std::string sku, int cents) {
        items_.push_back(std::make_unique<Item>(std::move(sku), cents));
        return *items_.back();
    }
    const Item& find(const std::string& sku) const {
        for (const auto& i : items_) if (i->sku() == sku) return *i;
        throw std::out_of_range("unknown sku " + sku);
    }
private:
    std::vector<std::unique_ptr<Item>> items_;
};

class Line {
public:
    Line(const Item& item, int qty) : item_(&item), qty_(qty) {}
    int cents() const { return item_->cents() * qty_; }
private:
    const Item* item_;
    int qty_;
};

class Order {
public:
    explicit Order(const Customer& customer) : customer_(&customer) { ++live_orders; }
    ~Order() { --live_orders; }
    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;
    void add(const Item& item, int qty) { lines_.emplace_back(item, qty); }
    int total() const { int sum = 0; for (const Line& l : lines_) sum += l.cents(); return sum; }
    const Customer& customer() const { return *customer_; }
private:
    const Customer* customer_;
    std::vector<Line> lines_;
};

class Shop {
public:
    explicit Shop(Mailer& mailer) : mailer_(mailer) {}
    Catalog& catalog() { return catalog_; }
    Order& place(const Customer& customer, const std::string& sku, int qty) {
        const Item& item = catalog_.find(sku);            // throws before anything is stored
        orders_.push_back(std::make_unique<Order>(customer));
        orders_.back()->add(item, qty);
        mailer_.send(customer.email(), "order confirmed");
        return *orders_.back();
    }
    std::size_t orders() const { return orders_.size(); }
private:
    Catalog catalog_;
    std::vector<std::unique_ptr<Order>> orders_;
    Mailer& mailer_;
};
