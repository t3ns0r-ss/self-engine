#include <bits/stdc++.h>
using namespace std;

string f(double x) {
    ostringstream o;
    o << fixed << setprecision(4) << x;
    string s = o.str();
    while (s.back() == '0') s.pop_back();
    if (s.back() == '.') s.pop_back();
    return s;
}
int main() {
    cout << fixed << setprecision(4);
    // P1: the expected number of fixed points of a random permutation of 4. Brute: average over the 24 permutations. Method: 4 * (1/4).
    vector<int> p = {0, 1, 2, 3};
    double total = 0, count = 0;
    do { count++; for (int i = 0; i < 4; i++) total += p[i] == i; } while (next_permutation(p.begin(), p.end()));
    cout << "P1 brute=" << f(total / count) << " method=" << f(4 * (1.0 / 4)) << '\n';
    // N1: the expected larger of two dice, computed as the larger of the two expected values.
    double sum = 0;
    for (int a = 1; a <= 6; a++) for (int b = 1; b <= 6; b++) sum += max(a, b);
    cout << "N1 brute=" << f(sum / 36) << " method=" << f(max(3.5, 3.5)) << '\n';
    // N2: the probability that a random permutation of 3 has a fixed point, computed as the expected number of fixed points.
    vector<int> q = {0, 1, 2};
    double any = 0, cnt = 0, fixedTotal = 0;
    do { cnt++; bool has = false; for (int i = 0; i < 3; i++) if (q[i] == i) has = true, fixedTotal++; any += has; } while (next_permutation(q.begin(), q.end()));
    cout << "N2 brute=" << f(any / cnt) << " method=" << f(fixedTotal / cnt) << '\n';
}
