#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.2. Counting by the last choice: ways[i] = the sum of ways[i - step] over the allowed steps.
vector<long long> climbs(int n, const vector<int>& steps) {
    vector<long long> ways(n + 1, 0);
    ways[0] = 1;  // the empty climb
    for (int i = 1; i <= n; i++)
        for (int s : steps)
            if (s <= i) ways[i] += ways[i - s];
    return ways;
}
// snippet:end

long long brute(int n, const vector<int>& steps) {  // list every sequence of steps
    if (n == 0) return 1;
    long long r = 0;
    for (int s : steps) if (s <= n) r += brute(n - s, steps);
    return r;
}
int main() {
    auto w = climbs(5, {1, 2});
    cout << "ways to climb 0..5 stairs with steps 1 or 2:";
    for (long long x : w) cout << ' ' << x;
    cout << '\n';
    for (int n = 0; n <= 12; n++) for (auto steps : vector<vector<int>>{{1, 2}, {1, 3, 4}, {2, 5}})
        if (climbs(n, steps)[n] != brute(n, steps)) return 1;
}
