// The mailed-first shop has the same classes and members as the checked-first shop. Only the order of two calls differs.
#include <cstdio>
#include <exception>
#include "mailed_first.hpp"

int main() {
    mailed_first::Inventory inv;
    mailed_first::Mailer mail;
    mailed_first::Shop shop(inv, mail);
    try { shop.place_order(5); } catch (const std::exception& e) { std::printf("order refused: %s\n", e.what()); }
    std::printf("confirmations sent: %d\n", mail.sent());
}
