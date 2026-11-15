#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: n, then a_1 .. a_n. A question "? i j" costs one of the n allowed; the answer must repeat the numbers.
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    int n;
    judge.hidden >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) judge.hidden >> a[i];
    judge.say(to_string(n));
    while (true) {
        stringstream line(judge.read());
        string op;
        line >> op;
        if (op == "?") {
            int i = 0, j = 0;
            line >> i >> j;
            if (i < 1 || i > n || j < 1 || j > n || i == j) judge.reject("bad pair");
            judge.query(n);
            judge.say(to_string(a[i] + a[j]));
        } else if (op == "!") {
            for (int i = 1; i <= n; i++) {
                long long v;
                if (!(line >> v) || v != a[i]) judge.finish("WA number " + to_string(i) + " is wrong");
            }
            judge.finish("OK queries=" + to_string(judge.queries));
        } else {
            judge.reject("a line that is neither ? nor !");
        }
    }
}
