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
    // P1: the rolls of a die until the first 6, rounded. Brute: the series sum of t * P(first 6 at t) over many terms. Method: 1/p.
    double series = 0;
    for (int t = 1; t <= 3000; t++) series += t * pow(5.0 / 6, t - 1) / 6;
    cout << "P1 brute=" << f(llround(series)) << " method=" << f(llround(1 / (1.0 / 6))) << '\n';
    // P2: the rolls until all six faces have appeared. Brute: value iteration on the number of faces seen. Method: 6 * H_6.
    vector<double> E(7, 0);
    for (int iter = 0; iter < 3000; iter++)
        for (int j = 5; j >= 0; j--) E[j] = 1 + (j / 6.0) * E[j] + ((6 - j) / 6.0) * E[j + 1];
    double method = 0;
    for (int j = 0; j < 6; j++) method += 6.0 / (6 - j);
    cout << "P2 brute=" << f(E[0]) << " method=" << f(method) << '\n' << setprecision(4);
    // N1: the probability of at least one 6 in 3 rolls, computed as the expected waiting time 1/p.
    cout << "N1 brute=" << f(1 - pow(5.0 / 6, 3)) << " method=" << f(6.0) << '\n';
    // N2: the draws without replacement from a bag of 2 red and 2 blue balls until the first red, computed as 1/p with p = 1/2.
    double e = 1 * (2.0 / 4) + 2 * (2.0 / 4 * 2.0 / 3) + 3 * (2.0 / 4 * 1.0 / 3 * 1.0);
    cout << "N2 brute=" << f(e) << " method=" << f(1 / 0.5) << '\n';
}
