#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "birds.hpp"

void every_bird_can_eat() {
    Sparrow s;
    Penguin p;
    const Bird& a = s;
    const Bird& b = p;
    CHECK(a.eat() == "sparrow eats");
    CHECK(b.eat() == "penguin eats");
}
void a_flying_bird_can_migrate() {
    Sparrow s;
    CHECK(migrate(s) == "sparrow flaps and flies south");
}
void a_penguin_cannot_be_asked_to_fly_because_the_promise_is_not_in_bird() {
    static_assert(CanFly<Sparrow>);
    static_assert(!CanFly<Penguin>);
    static_assert(!std::is_base_of_v<FlyingBird, Penguin>);
    CHECK(CanFly<Sparrow>);
    CHECK(!CanFly<Penguin>);
}
void a_penguin_does_what_penguins_do() {
    Penguin p;
    CHECK(p.swim() == "penguin swims");
}
void a_mixed_flock_is_eaten_through_the_base() {
    std::vector<std::unique_ptr<Bird>> flock;
    flock.push_back(std::make_unique<Sparrow>());
    flock.push_back(std::make_unique<Penguin>());
    int fed = 0;
    for (const auto& b : flock) fed += b->eat().empty() ? 0 : 1;
    CHECK(fed == 2);
}

int main() {
    RUN(every_bird_can_eat);
    RUN(a_flying_bird_can_migrate);
    RUN(a_penguin_cannot_be_asked_to_fly_because_the_promise_is_not_in_bird);
    RUN(a_penguin_does_what_penguins_do);
    RUN(a_mixed_flock_is_eaten_through_the_base);
    return check::report();
}
