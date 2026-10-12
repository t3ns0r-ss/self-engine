#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.5.4. g(i) depends only on the previous m = max(removals) values, so once the same window of m values appears twice,
// the sequence repeats from there on. Returns g(n) for a huge n by finding the first repeated window.
int grundyBig(const vector<int>& removals, long long n) {
    int m = *max_element(removals.begin(), removals.end());
    vector<int> g;
    map<vector<int>, int> firstSeen;  // the window of the last m values -> the position after it
    for (int i = 0;; i++) {
        if (n < i) return g[n];
        if (i >= m) {
            auto [it, fresh] = firstSeen.emplace(vector<int>(g.end() - m, g.end()), i);
            if (!fresh) {
                int start = it->second, period = i - start;
                return g[start + (n - start) % period];
            }
        }
        set<int> reach;
        for (int r : removals)
            if (r <= i) reach.insert(g[i - r]);
        int mex = 0;
        while (reach.count(mex)) mex++;
        g.push_back(mex);
    }
}
// snippet:end

int bruteGrundy(const vector<int>& removals, int n) {
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        set<int> reach;
        for (int r : removals)
            if (r <= x) reach.insert(g[x - r]);
        while (reach.count(g[x])) g[x]++;
    }
    return g[n];
}

int main() {
    cout << "g(100) for 1 3 4: " << grundyBig({1, 3, 4}, 100) << "\n";
    cout << "g(10^18) for 1 3 4: " << grundyBig({1, 3, 4}, 1000000000000000000LL) << "\n";
    cout << "g(10^18) for 1 2: " << grundyBig({1, 2}, 1000000000000000000LL) << "\n";
    // Check (not printed): 300 random removal sets of up to 4 numbers from 1 to 7 and every n up to 300, against the plain table.
    mt19937 rng(32);
    for (int it = 0; it < 300; it++) {
        set<int> s;
        int k = rng() % 4 + 1;
        while ((int)s.size() < k) s.insert(rng() % 7 + 1);
        vector<int> rem(s.begin(), s.end());
        for (int n = 0; n <= 300; n++)
            if (grundyBig(rem, n) != bruteGrundy(rem, n)) return 1;
    }
}
