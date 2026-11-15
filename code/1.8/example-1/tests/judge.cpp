#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: "n budget" then the string S. Any p with S_p != S_{p+1} is right.
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    int n, budget;
    string s;
    judge.hidden >> n >> budget >> s;
    judge.say(to_string(n));
    while (true) {
        stringstream line(judge.read());
        string op;
        int value = 0;
        line >> op >> value;
        if (op == "?") {
            if (value < 1 || value > n) judge.reject("question outside 1..n");
            judge.query(budget);
            judge.say(string(1, s[value - 1]));
        } else if (op == "!") {
            if (value < 1 || value >= n || s[value - 1] == s[value]) judge.finish("WA position " + to_string(value) + " is not a change");
            judge.finish("OK queries=" + to_string(judge.queries));
        } else {
            judge.reject("a line that is neither ? nor !");
        }
    }
}
