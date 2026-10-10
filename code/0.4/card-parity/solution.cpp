#include <bits/stdc++.h>
using namespace std;

// Is the cell (x, y) reachable from (0, 0) in exactly t side steps? Brute: expand the set of cells step by step.
bool brute(int x, int y, int t) {
    set<pair<int, int>> now = {{0, 0}};
    for (int i = 0; i < t; i++) {
        set<pair<int, int>> next;
        for (auto [a, b] : now) next.insert({a + 1, b}), next.insert({a - 1, b}), next.insert({a, b + 1}), next.insert({a, b - 1});
        now = next;
    }
    return now.count({x, y}) > 0;
}
bool parityOnly(int x, int y, int t) { return (abs(x) + abs(y)) % 2 == t % 2; }
bool withDistance(int x, int y, int t) { return abs(x) + abs(y) <= t && (t - abs(x) - abs(y)) % 2 == 0; }
const char* yn(bool b) { return b ? "yes" : "no"; }

int main() {
    cout << "P1 brute=" << yn(brute(0, 0, 6)) << " method=" << yn(withDistance(0, 0, 6)) << '\n';
    cout << "P2 brute=" << yn(brute(1, 2, 5)) << " method=" << yn(withDistance(1, 2, 5)) << '\n';
    // N1: (5, 0) in 3 steps. Parity alone says yes (5 and 3 are both odd); the distance 5 is more than 3.
    cout << "N1 brute=" << yn(brute(5, 0, 3)) << " method=" << yn(parityOnly(5, 0, 3)) << '\n';
    // N2: from 5, each move subtracts 1 or 2. Can 5 become 0 in exactly 4 moves? Brute: try all. Method: "every move
    // flips the parity", so after 4 moves the parity of 5 is odd, while 0 is even.
    bool any = false;
    for (int a = 1; a <= 2; a++) for (int b = 1; b <= 2; b++) for (int c = 1; c <= 2; c++) for (int d = 1; d <= 2; d++) any |= 5 - a - b - c - d == 0;
    bool flips = ((5 + 4) % 2) == (0 % 2);
    cout << "N2 brute=" << yn(any) << " method=" << yn(flips) << '\n';
}
