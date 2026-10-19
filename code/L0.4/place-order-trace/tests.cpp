#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "check.hpp"
#include "model.hpp"

// Runs one scenario, with the test as the caller, and saves the recorded trace for the diagram check.
template <class F> std::vector<std::string> run_traced(const char* name, F scenario) {
    trace.clear();
    call("Test", "Shop", "place_order");
    try { scenario(); } catch (const std::exception&) {}
    if (const char* dir = std::getenv("TRACE_DIR")) {
        std::ofstream out(std::string(dir) + "/" + name + ".txt");
        for (const auto& l : trace) out << l << "\n";
    }
    return trace;
}

void a_paid_order_reserves_charges_and_mails_in_that_order() {
    Inventory inv; inv.stock("pen", 5); Payments pay(10000); Mailer mail; Shop shop(inv, pay, mail);
    auto t = run_traced("ok", [&] { shop.place_order("ann@example.com", "pen", 2, 150); });
    CHECK((t == std::vector<std::string>{"Test->Shop: place_order", "Shop->Inventory: reserve", "Shop->Payments: charge", "Shop->Mailer: send"}));
    CHECK(inv.have("pen") == 3);
    CHECK(mail.sent() == 1);
}
void an_order_out_of_stock_stops_after_the_reserve() {
    Inventory inv; inv.stock("pen", 1); Payments pay(10000); Mailer mail; Shop shop(inv, pay, mail);
    auto t = run_traced("out_of_stock", [&] { shop.place_order("ann@example.com", "pen", 2, 150); });
    CHECK((t == std::vector<std::string>{"Test->Shop: place_order", "Shop->Inventory: reserve"}));
    CHECK(inv.have("pen") == 1);
    CHECK(mail.sent() == 0);
}
void a_declined_payment_gives_the_stock_back_and_sends_no_mail() {
    Inventory inv; inv.stock("pen", 5); Payments pay(100); Mailer mail; Shop shop(inv, pay, mail);
    auto t = run_traced("declined", [&] { shop.place_order("ann@example.com", "pen", 2, 150); });
    CHECK((t == std::vector<std::string>{"Test->Shop: place_order", "Shop->Inventory: reserve", "Shop->Payments: charge", "Shop->Inventory: release"}));
    CHECK(inv.have("pen") == 5);
    CHECK(mail.sent() == 0);
}

int main() {
    RUN(a_paid_order_reserves_charges_and_mails_in_that_order);
    RUN(an_order_out_of_stock_stops_after_the_reserve);
    RUN(a_declined_payment_gives_the_stock_back_and_sends_no_mail);
    return check::report();
}
