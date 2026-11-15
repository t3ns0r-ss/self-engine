#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: n, then the judge's preference order. The judge names the first number of the order that is unused.
// Each number of ours is a query for the counter (the game has no budget, so the budget is huge).
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    int n;
    judge.hidden >> n;
    vector<int> order(2 * n + 1);
    for (int& v : order) judge.hidden >> v;
    vector<bool> used(2 * n + 2, false);
    judge.say(to_string(n));
    while (true) {
        int mine = 0;
        stringstream line(judge.read());
        if (!(line >> mine) || mine < 1 || mine > 2 * n + 1 || used[mine]) judge.reject("a number that is not allowed");
        judge.query(1 << 20);
        used[mine] = true;
        int theirs = 0;
        for (int v : order)
            if (!used[v]) {
                theirs = v;
                break;
            }
        if (theirs == 0) {
            judge.say("0");
            judge.finish("OK moves=" + to_string(judge.queries));
        }
        used[theirs] = true;
        judge.say(to_string(theirs));
    }
}
