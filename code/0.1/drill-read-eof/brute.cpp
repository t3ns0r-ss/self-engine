#include <bits/stdc++.h>
using namespace std;

// Brute force: read the whole input as text, then split it into numbers.
int main() {
    string all, line;
    while (getline(cin, line)) all += line + " ";
    istringstream in(all);
    vector<long long> v;
    string tok;
    while (in >> tok) v.push_back(stoll(tok));
    long long sum = 0, best = v[0];
    for (long long x : v) { sum += x; best = max(best, x); }
    cout << v.size() << " " << sum << " " << best << "\n";
}
