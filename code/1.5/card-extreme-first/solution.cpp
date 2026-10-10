#include <bits/stdc++.h>
using namespace std;

int fewest(vector<int> v, int T, bool largestFirst) {
    sort(v.begin(), v.end());
    if (largestFirst) reverse(v.begin(), v.end());
    int sum = 0;
    for (int k = 0; k < (int)v.size(); k++) if ((sum += v[k]) >= T) return k + 1;
    return -1;
}

int main() {
    // P1: the fewest of 5 1 4 2 with sum at least 9. Brute: every subset. Method: largest first.
    vector<int> v = {5, 1, 4, 2};
    int brute = -1;
    for (int mask = 0; mask < 16; mask++) {
        int s = 0;
        for (int i = 0; i < 4; i++) if (mask >> i & 1) s += v[i];
        if (s >= 9 && (brute < 0 || __builtin_popcount(mask) < brute)) brute = __builtin_popcount(mask);
    }
    cout << "P1 brute=" << brute << " method=" << fewest(v, 9, true) << '\n';
    // N1: capacity 10, items (size, value) = (6, 7), (5, 5), (5, 5), unsplittable. Method: the item with the best
    // value per size first.
    vector<array<int, 2>> it = {{6, 7}, {5, 5}, {5, 5}};
    int best = 0;
    for (int mask = 0; mask < 8; mask++) {
        int size = 0, val = 0;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) size += it[i][0], val += it[i][1];
        if (size <= 10) best = max(best, val);
    }
    int room = 10, greedy = 0;
    for (auto& x : it) if (x[0] <= room) room -= x[0], greedy += x[1];
    cout << "N1 brute=" << best << " method=" << greedy << '\n';
    // N2: the fewest of 5 1 4 2 with sum at least 9, taking the smallest first.
    cout << "N2 brute=" << brute << " method=" << fewest(v, 9, false) << '\n';
}
