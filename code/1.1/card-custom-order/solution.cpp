#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: standings of three contestants (solved, penalty) = (2, 50), (3, 90), (3, 40): more solved first, then less
    // penalty. Brute: repeatedly pick the best remaining. Method: sort with a comparator.
    vector<array<int, 3>> c = {{2, 50, 1}, {3, 90, 2}, {3, 40, 3}};
    auto before = [](const array<int, 3>& x, const array<int, 3>& y) { return x[0] != y[0] ? x[0] > y[0] : x[1] < y[1]; };
    vector<array<int, 3>> rest = c;
    string brute, method;
    while (!rest.empty()) {
        int best = 0;
        for (int i = 1; i < (int)rest.size(); i++) if (before(rest[i], rest[best])) best = i;
        brute += (brute.empty() ? "" : ",") + to_string(rest[best][2]);
        rest.erase(rest.begin() + best);
    }
    sort(c.begin(), c.end(), before);
    for (auto& x : c) method += (method.empty() ? "" : ",") + to_string(x[2]);
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the largest number joining 3 30 34 5 9. Brute: every order. Method: sort with x + y > y + x.
    vector<string> s = {"3", "30", "34", "5", "9"}, t = s;
    sort(t.begin(), t.end());
    string best;
    do {
        string j;
        for (auto& x : t) j += x;
        if (j > best) best = j;
    } while (next_permutation(t.begin(), t.end()));
    sort(s.begin(), s.end(), [](const string& x, const string& y) { return x + y > y + x; });
    string joined;
    for (auto& x : s) joined += x;
    cout << "P2 brute=" << best << " method=" << joined << '\n';
    // N1: the largest number joining 12 and 121, ordered by plain descending string order.
    vector<string> u = {"12", "121"};
    sort(u.begin(), u.end(), greater<string>());
    cout << "N1 brute=" << max(string("12") + "121", string("121") + "12") << " method=" << u[0] + u[1] << '\n';
    // N2: which of 999999999999999999 / 1000000000000000000 and 999999999999999998 / 999999999999999999 is larger?
    // Brute: cross-multiplication in 128 bits. Method: the two quotients as doubles.
    long long p1 = 999999999999999999LL, q1 = 1000000000000000000LL, p2 = 999999999999999998LL, q2 = 999999999999999999LL;
    bool exact = (__int128)p1 * q2 > (__int128)p2 * q1;
    bool dbl = (double)p1 / q1 > (double)p2 / q2;
    cout << "N2 brute=" << (exact ? "first" : "equal") << " method=" << (dbl ? "first" : "equal") << '\n';
}
