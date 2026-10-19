#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "kit.hpp"

void the_engine_is_built_before_the_car_and_destroyed_after_it() {
    events.clear();
    {
        Car car;
        CHECK((events == std::vector<std::string>{"engine built", "car built"}));
    }
    CHECK((events == std::vector<std::string>{"engine built", "car built", "car destroyed", "engine destroyed"}));
}
void starting_the_car_starts_its_own_engine() {
    Car a, b;
    a.start();
    CHECK(a.running());
    CHECK(!b.running());
}
void a_part_held_by_value_costs_no_pointer() {
    static_assert(sizeof(Car) == sizeof(Engine), "the engine must be a member held by value");
    CHECK(sizeof(Car) == sizeof(Engine));
}
void a_car_in_a_unique_ptr_destroys_its_engine() {
    events.clear();
    { auto car = std::make_unique<Car>(); }
    CHECK(events.size() == 4);
    CHECK(events.back() == "engine destroyed");
}

static_assert(!CanAddTemporary<Team>, "a temporary Player would be gone before the team is used");

void players_stay_valid_after_the_team_is_gone() {
    Player ann("ann", 7), bo("bo", 5);
    CHECK(live_players == 2);
    {
        Team t;
        t.add(ann);
        t.add(bo);
        CHECK(t.size() == 2);
        CHECK(t.total_score() == 12);
    }
    CHECK(live_players == 2);
    CHECK(ann.name == "ann");
    CHECK(bo.score == 5);
}
void the_team_sees_changes_made_to_a_player() {
    Player ann("ann", 7);
    Team t;
    t.add(ann);
    ann.score = 10;
    CHECK(t.total_score() == 10);
}
void adding_a_player_copies_nothing() {
    player_copies = 0;
    Player ann("ann", 1), bo("bo", 2), cy("cy", 3);
    Team t;
    t.add(ann);
    t.add(bo);
    t.add(cy);
    CHECK(player_copies == 0);
    CHECK((t.names() == std::vector<std::string>{"ann", "bo", "cy"}));
}
void two_teams_can_refer_to_the_same_player() {
    Player ann("ann", 4);
    Team a, b;
    a.add(ann);
    b.add(ann);
    ann.score = 9;
    CHECK(a.total_score() == 9);
    CHECK(b.total_score() == 9);
}
void an_empty_team_has_no_score() {
    Team t;
    CHECK(t.size() == 0);
    CHECK(t.total_score() == 0);
    CHECK(t.names().empty());
}

static_assert(!std::is_base_of_v<Rect, Square>, "a Square cannot keep the promises of a Rect, so it must not derive from it");

void a_square_has_a_side_and_an_area() {
    Square s(5);
    CHECK(s.side() == 5);
    CHECK(s.area() == 25);
    CHECK(Square(0).area() == 0);
}
void scaling_builds_a_new_square() {
    Square s(2);
    Square t = s.scaled(3);
    CHECK(s.side() == 2);
    CHECK(t.side() == 6);
    CHECK(t.area() == 36);
}
void a_square_becomes_a_rect_of_equal_sides() {
    Rect r = Square(5).as_rect();
    CHECK(r.width() == 5);
    CHECK(r.height() == 5);
    CHECK(r.area() == 25);
}
void the_rect_made_from_a_square_keeps_the_rect_promise() {
    Rect r = Square(4).as_rect();
    CHECK(keeps_rect_promise(r));
    CHECK(r.area() == 35);               // the promise test left it 5 wide and 7 high
}
void a_plain_rect_keeps_its_promise() {
    Rect r(3, 4);
    CHECK(keeps_rect_promise(r));
}

static_assert(!std::is_default_constructible_v<Cart>, "a Cart is given its Logger");
static_assert(!std::is_default_constructible_v<Checkout>, "a Checkout is given its Logger");
static_assert(!std::is_default_constructible_v<Mailer>, "a Mailer is given its Logger");

void three_classes_share_one_logger_in_order() {
    MemoryLogger log;
    Cart cart(log);
    Checkout checkout(log);
    Mailer mailer(log);
    cart.add("apple");
    CHECK(checkout.pay(250) == 250);
    mailer.send("ann");
    CHECK((log.lines == std::vector<std::string>{"cart: added apple", "checkout: paid 250", "mailer: sent to ann"}));
}
void the_cart_keeps_its_items() {
    MemoryLogger log;
    Cart cart(log);
    cart.add("a");
    cart.add("b");
    CHECK(cart.size() == 2);
    CHECK(log.lines.size() == 2);
}
void a_refused_payment_logs_nothing() {
    MemoryLogger log;
    Checkout checkout(log);
    CHECK_THROWS(checkout.pay(0));
    CHECK_THROWS(checkout.pay(-5));
    CHECK(log.lines.empty());
}
void a_logger_written_by_the_caller_works_unchanged() {
    struct Counting final : Logger {
        int n = 0;
        void log(const std::string&) override { ++n; }
    };
    Counting c;
    Cart cart(c);
    Mailer mailer(c);
    cart.add("x");
    mailer.send("bo");
    CHECK(c.n == 2);
}
void the_logger_outlives_the_classes_that_use_it() {
    MemoryLogger log;
    {
        Cart cart(log);
        cart.add("x");
    }
    CHECK(log.lines.size() == 1);
}

static_assert(!std::is_base_of_v<Invoice, Receipt> && !std::is_base_of_v<Receipt, Invoice>, "reuse the formatting with a free function, not a hierarchy");
static_assert(!std::is_polymorphic_v<Invoice> && !std::is_polymorphic_v<Receipt>, "no virtual function is needed");
static_assert(sizeof(Invoice) == sizeof(long long) && sizeof(Receipt) == sizeof(long long), "no hidden pointer");

void cents_are_formatted_with_two_decimals() {
    CHECK(format_cents(1205) == "12.05");
    CHECK(format_cents(5) == "0.05");
    CHECK(format_cents(0) == "0.00");
    CHECK(format_cents(100) == "1.00");
    CHECK(format_cents(123456789) == "1234567.89");
}
void a_negative_amount_keeps_its_sign() {
    CHECK(format_cents(-50) == "-0.50");
    CHECK(format_cents(-1205) == "-12.05");
}
void an_invoice_says_invoice() { CHECK(Invoice(1205).total_text() == "Invoice total 12.05"); }
void a_receipt_says_receipt() { CHECK(Receipt(5).total_text() == "Receipt total 0.05"); }

int main() {
    RUN(the_engine_is_built_before_the_car_and_destroyed_after_it);
    RUN(starting_the_car_starts_its_own_engine);
    RUN(a_part_held_by_value_costs_no_pointer);
    RUN(a_car_in_a_unique_ptr_destroys_its_engine);
    RUN(players_stay_valid_after_the_team_is_gone);
    RUN(the_team_sees_changes_made_to_a_player);
    RUN(adding_a_player_copies_nothing);
    RUN(two_teams_can_refer_to_the_same_player);
    RUN(an_empty_team_has_no_score);
    RUN(a_square_has_a_side_and_an_area);
    RUN(scaling_builds_a_new_square);
    RUN(a_square_becomes_a_rect_of_equal_sides);
    RUN(the_rect_made_from_a_square_keeps_the_rect_promise);
    RUN(a_plain_rect_keeps_its_promise);
    RUN(three_classes_share_one_logger_in_order);
    RUN(the_cart_keeps_its_items);
    RUN(a_refused_payment_logs_nothing);
    RUN(a_logger_written_by_the_caller_works_unchanged);
    RUN(the_logger_outlives_the_classes_that_use_it);
    RUN(cents_are_formatted_with_two_decimals);
    RUN(a_negative_amount_keeps_its_sign);
    RUN(an_invoice_says_invoice);
    RUN(a_receipt_says_receipt);
    return check::report();
}
