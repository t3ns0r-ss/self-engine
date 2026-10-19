#include <cstdio>
#include <vector>

struct Player { int score; };

class Team {
public:
    void add(const Player& p) { members_.push_back(&p); }
    int total() const {
        int sum = 0;
        for (const Player* p : members_) sum += p->score;
        return sum;
    }
private:
    std::vector<const Player*> members_;           // refers to players it does not own
};

int main() {
    Team team;
    Player* ann = new Player{7};
    team.add(*ann);
    delete ann;                                    // MISTAKE: the part was destroyed first; the team still points at it
    std::printf("total = %d\n", team.total());
}
