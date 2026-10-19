#include <string>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "team.hpp"

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
    CHECK(live_players == 2);                    // the team's destructor destroyed nobody
    CHECK(ann.name == "ann");
    CHECK(bo.score == 5);
}
void the_team_sees_changes_made_to_a_player() {
    Player ann("ann", 7);
    Team t;
    t.add(ann);
    ann.score = 10;
    CHECK(t.total_score() == 10);                // it refers to the player, it does not hold a copy
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
void a_temporary_player_cannot_be_added() {
    static_assert(!CanAddTemporary<Team>);
    CHECK(!CanAddTemporary<Team>);
}

int main() {
    RUN(players_stay_valid_after_the_team_is_gone);
    RUN(the_team_sees_changes_made_to_a_player);
    RUN(adding_a_player_copies_nothing);
    RUN(two_teams_can_refer_to_the_same_player);
    RUN(a_temporary_player_cannot_be_added);
    return check::report();
}
