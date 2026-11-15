#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: n x budget mode. mode "fixed" answers for the number x; mode "adaptive" ignores x and answers each
// question so that the larger group of numbers stays possible (ties: answer 0). The answer must then be the only
// number left that agrees with all the replies.
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    long long n, x, budget;
    string mode;
    judge.hidden >> n >> x >> budget >> mode;
    judge.say(to_string(n));
    long long lo = 1, hi = n;  // the numbers that still agree with every reply
    while (true) {
        stringstream line(judge.read());
        string op;
        long long value = 0;
        line >> op >> value;
        if (op == "?") {
            if (value < 1 || value > n) judge.reject("question outside 1..n");
            judge.query(budget);
            bool yes;
            if (mode == "fixed") {
                yes = x <= value;
            } else {
                long long yesSize = max(0LL, min(hi, value) - lo + 1);
                long long noSize = max(0LL, hi - max(lo, value + 1) + 1);
                yes = yesSize > noSize;
            }
            if (yes) hi = min(hi, value);
            else lo = max(lo, value + 1);
            judge.say(yes ? "1" : "0");
        } else if (op == "!") {
            if (mode == "fixed") {
                if (value != x) judge.finish("WA wrong answer " + to_string(value) + ", the hidden number is " + to_string(x));
            } else if (lo != hi || value != lo) {
                judge.finish("WA the answer " + to_string(value) + " is not forced by the replies: the numbers " + to_string(lo) + ".." + to_string(hi) + " all agree");
            }
            judge.finish("OK queries=" + to_string(judge.queries));
        } else {
            judge.reject("a line that is neither ? nor !");
        }
    }
}
