#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: "n budget" then a_1 .. a_n. The answer p must be smaller than both neighbours (outside = infinity).
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    int n, budget;
    judge.hidden >> n >> budget;
    vector<long long> a(n + 2, LLONG_MAX);
    for (int i = 1; i <= n; i++) judge.hidden >> a[i];
    judge.say(to_string(n));
    while (true) {
        stringstream line(judge.read());
        string op;
        int value = 0;
        line >> op >> value;
        if (op == "?") {
            if (value < 1 || value > n) judge.reject("question outside 1..n");
            judge.query(budget);
            judge.say(to_string(a[value]));
        } else if (op == "!") {
            if (value < 1 || value > n || !(a[value] < a[value - 1] && a[value] < a[value + 1]))
                judge.finish("WA position " + to_string(value) + " is not a local minimum");
            judge.finish("OK queries=" + to_string(judge.queries));
        } else {
            judge.reject("a line that is neither ? nor !");
        }
    }
}
