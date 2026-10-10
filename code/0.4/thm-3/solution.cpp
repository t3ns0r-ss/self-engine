#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.3. A walker moves one side step at a time. It can go a distance d in exactly t steps
// only if d <= t and t - d is even: each step flips the parity of x + y.
bool canWalk(long long d, long long t) { return d <= t && (t - d) % 2 == 0; }
// snippet:end

int main() {
    cout << "back to the start (d = 0) in 7 steps: " << (canWalk(0, 7) ? "yes" : "no") << '\n';
    cout << "back to the start (d = 0) in 6 steps: " << (canWalk(0, 6) ? "yes" : "no") << '\n';
    cout << "to (1, 2) (d = 3) in 5 steps: " << (canWalk(3, 5) ? "yes" : "no") << '\n';
    set<pair<int, int>> now = {{0, 0}};  // the cells reachable in exactly t steps, for t up to 8
    for (int t = 0; t <= 8; t++) {
        for (int x = -9; x <= 9; x++)
            for (int y = -9; y <= 9; y++)
                if (now.count({x, y}) != canWalk(abs(x) + abs(y), t)) return 1;
        set<pair<int, int>> next;
        for (auto [x, y] : now) next.insert({x + 1, y}), next.insert({x - 1, y}), next.insert({x, y + 1}), next.insert({x, y - 1});
        now = next;
    }
}
