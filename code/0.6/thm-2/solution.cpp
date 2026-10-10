#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.2. The number of distinct values, and whether a value occurs, with a set.
int distinctCount(const vector<int>& a) { return set<int>(a.begin(), a.end()).size(); }
bool occurs(const vector<int>& a, int x) { return set<int>(a.begin(), a.end()).count(x) > 0; }
// snippet:end

int main() {
    vector<int> a = {3, 1, 3, 3};
    cout << "distinct values in 3 1 3 3: " << distinctCount(a) << '\n';
    cout << "is 1 present: " << (occurs(a, 1) ? "yes" : "no") << '\n';
    cout << "is 2 present: " << (occurs(a, 2) ? "yes" : "no") << '\n';
    mt19937 rng(1);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8;
        vector<int> b(n);
        for (int& x : b) x = rng() % 5;
        int distinct = 0;
        for (int v = 0; v < 5; v++) {
            bool seen = false;
            for (int x : b) seen |= x == v;
            distinct += seen;
            if (seen != occurs(b, v)) return 1;
        }
        if (distinct != distinctCount(b)) return 1;
    }
}
