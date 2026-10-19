// Aggregation: a Team refers to Players that exist on their own. It never builds, copies or destroys them.
#pragma once
#include <concepts>
#include <string>
#include <vector>

inline int live_players = 0;     // how many Player objects exist right now
inline int player_copies = 0;    // how many times a Player was copied

struct Player {
    std::string name;
    int score = 0;
    Player(std::string n, int s) : name(std::move(n)), score(s) { ++live_players; }
    Player(const Player& o) : name(o.name), score(o.score) { ++live_players; ++player_copies; }
    Player& operator=(const Player&) = default;
    ~Player() { --live_players; }
};

class Team {
public:
    void add(const Player& p) { members_.push_back(&p); }   // keeps the address: the player must outlive the team
    void add(Player&&) = delete;                            // a temporary would be gone before the team is used
    std::size_t size() const { return members_.size(); }
    int total_score() const {
        int sum = 0;
        for (const Player* p : members_) sum += p->score;
        return sum;
    }
    std::vector<std::string> names() const {
        std::vector<std::string> out;
        for (const Player* p : members_) out.push_back(p->name);
        return out;
    }
private:
    std::vector<const Player*> members_;                    // non-owning: nothing here is ever deleted
};

template <class T> concept CanAddTemporary = requires(T t) { t.add(Player{"tmp", 0}); };
