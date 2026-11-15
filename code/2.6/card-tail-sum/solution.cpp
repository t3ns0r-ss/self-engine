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
double expectedMax(int m, int k) {
    double e = 0;
    for (int x = 1; x <= m; x++) e += 1 - pow((x - 1.0) / m, k);
    return e;
}
double expectedMin(int m, int k) {
    double e = 0;
    for (int x = 1; x <= m; x++) e += pow((m - x + 1.0) / m, k);
    return e;
}
int main() {
    cout << fixed << setprecision(4);
    // P1: the larger of two dice. P2: the smaller of two dice. Brute: all 36 outcomes. Method: tail sums.
    double mx = 0, mn = 0;
    for (int a = 1; a <= 6; a++) for (int b = 1; b <= 6; b++) mx += max(a, b), mn += min(a, b);
    cout << "P1 brute=" << f(mx / 36) << " method=" << f(expectedMax(6, 2)) << '\n';
    cout << "P2 brute=" << f(mn / 36) << " method=" << f(expectedMin(6, 2)) << '\n';
    // N1: the larger of two cards drawn without replacement from 1..6, with the independent formula.
    double drawn = 0;
    for (int a = 1; a <= 6; a++) for (int b = 1; b <= 6; b++) if (a != b) drawn += max(a, b);
    cout << "N1 brute=" << f(drawn / 30) << " method=" << f(expectedMax(6, 2)) << '\n';
    // N2: the sum of two dice, computed with the maximum formula.
    cout << "N2 brute=" << f(7.0) << " method=" << f(expectedMax(6, 2)) << '\n';
}
