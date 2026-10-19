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

int main() {
    RUN(the_engine_is_built_before_the_car_and_destroyed_after_it);
    RUN(starting_the_car_starts_its_own_engine);
    RUN(a_part_held_by_value_costs_no_pointer);
    RUN(a_car_in_a_unique_ptr_destroys_its_engine);
    return check::report();
}
