#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "parts.hpp"

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
    CHECK(!b.running());                         // each car has its own engine
}
void a_part_held_by_value_costs_no_pointer() {
    static_assert(sizeof(Car) == sizeof(Engine));
    CHECK(sizeof(Car) == sizeof(Engine));
}
void a_car_cannot_be_copied_because_its_engine_cannot() {
    static_assert(!std::is_copy_constructible_v<Car>);
    CHECK(!std::is_copy_constructible_v<Car>);
}
void destroying_the_car_through_a_unique_ptr_destroys_the_engine() {
    events.clear();
    { auto car = std::make_unique<Car>(); }
    CHECK(events.back() == "engine destroyed");
    CHECK(events.size() == 4);
}

int main() {
    RUN(the_engine_is_built_before_the_car_and_destroyed_after_it);
    RUN(starting_the_car_starts_its_own_engine);
    RUN(a_part_held_by_value_costs_no_pointer);
    RUN(a_car_cannot_be_copied_because_its_engine_cannot);
    RUN(destroying_the_car_through_a_unique_ptr_destroys_the_engine);
    return check::report();
}
