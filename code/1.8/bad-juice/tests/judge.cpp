#include "../../../shared/interact/interact.hpp"
using namespace std;

// Hidden test: "n x mode". The judge needs the fewest friends (m with 2^m >= n). Mode "fixed": bottle x is bad.
// Mode "adaptive": after seeing which bottles each friend drinks, the judge replies with the sickness pattern that
// fits the most bottles (ties: the pattern that comes first as a string); the answer must then be the only bottle
// that fits the pattern.
int main(int argc, char** argv) {
    Judge judge(argc, argv);
    int n, x;
    string mode;
    judge.hidden >> n >> x >> mode;
    judge.say(to_string(n));
    int need = 0;
    while ((1 << need) < n) need++;
    stringstream first(judge.read());
    int m = -1;
    first >> m;
    if (m != need) judge.finish("WA " + to_string(m) + " friends, the fewest is " + to_string(need));
    vector<string> pattern(n + 1, string(m, '0'));
    for (int j = 0; j < m; j++) {
        stringstream line(judge.read());
        int k = 0;
        line >> k;
        for (int t = 0; t < k; t++) {
            int b = 0;
            line >> b;
            if (b < 1 || b > n) judge.reject("bottle outside 1..n");
            pattern[b][j] = '1';
        }
    }
    string reply = pattern[x];
    if (mode == "adaptive") {
        map<string, int> fits;
        for (int b = 1; b <= n; b++) fits[pattern[b]]++;
        int best = 0;
        for (auto& [p, c] : fits)
            if (c > best) best = c, reply = p;
    }
    judge.say(reply);
    stringstream last(judge.read());
    int bad = 0;
    last >> bad;
    int count = 0;
    for (int b = 1; b <= n; b++) count += pattern[b] == reply;
    if (mode == "fixed" ? bad != x : (bad < 1 || bad > n || pattern[bad] != reply || count != 1))
        judge.finish("WA bottle " + to_string(bad) + " is not forced by the replies");
    judge.finish("OK friends=" + to_string(m));
}
