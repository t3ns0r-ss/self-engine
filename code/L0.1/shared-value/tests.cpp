#include <memory>
#include <type_traits>

#include "address.hpp"
#include "check.hpp"

static_assert(!std::is_aggregate_v<Address>);
static_assert(std::is_same_v<decltype(std::declval<const Order&>().address()), const Address&>, "readers get a const view");

void two_orders_can_share_one_address_object() {
    auto a = std::make_shared<const Address>("1 Main St", "Oslo");
    Order o1(a), o2(a);
    CHECK(o1.address_identity() == o2.address_identity());
    CHECK(a.use_count() == 3);
}
void changing_one_order_leaves_the_other_alone() {
    auto a = std::make_shared<const Address>("1 Main St", "Oslo");
    Order o1(a), o2(a);
    o1.change_address(std::make_shared<const Address>(a->with_street("9 Side St")));
    CHECK(o1.address().street() == "9 Side St");
    CHECK(o2.address().street() == "1 Main St");
    CHECK(a->street() == "1 Main St");
}
void with_street_builds_a_new_value() {
    Address a("1 Main St", "Oslo");
    Address b = a.with_street("2 Main St");
    CHECK(a.street() == "1 Main St");
    CHECK(b.street() == "2 Main St");
    CHECK(b.city() == "Oslo");
}
void an_empty_field_is_refused() {
    CHECK_THROWS(Address("", "Oslo"));
    CHECK_THROWS(Address("1 Main St", ""));
    Address ok("1 Main St", "Oslo");
    CHECK_THROWS(ok.with_street(""));
    CHECK(ok.street() == "1 Main St");
}
void equal_fields_mean_equal_values() {
    CHECK(Address("a", "b") == Address("a", "b"));
    CHECK(!(Address("a", "b") == Address("a", "c")));
}
void the_old_value_lives_on_while_someone_holds_it() {
    auto a = std::make_shared<const Address>("1 Main St", "Oslo");
    Order o1(a);
    a.reset();
    CHECK(o1.address().city() == "Oslo");
}
int main() {
    RUN(two_orders_can_share_one_address_object);
    RUN(changing_one_order_leaves_the_other_alone);
    RUN(with_street_builds_a_new_value);
    RUN(an_empty_field_is_refused);
    RUN(equal_fields_mean_equal_values);
    RUN(the_old_value_lives_on_while_someone_holds_it);
    return check::report();
}
