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
    return check::report();
}
