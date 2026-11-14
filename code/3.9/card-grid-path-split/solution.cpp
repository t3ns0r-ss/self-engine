#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<long long>> Grid;

// paths from the top-left to the bottom-right cell (right and down moves) with xor k; the flag adds the meeting cell to the backward xor too
long long halves(const Grid& a, long long k, bool meetingCellTwice) {
    int n = a.size(), m = a[0].size(), half = (n + m - 2) / 2;
    vector<map<long long, long long>> forward(n);
    function<void(int, int, long long)> goForward = [&](int i, int j, long long x) {
        x ^= a[i][j];
        if (i + j == half) { forward[i][x]++; return; }
        if (i + 1 < n) goForward(i + 1, j, x);
        if (j + 1 < m) goForward(i, j + 1, x);
    };
    goForward(0, 0, 0);
    long long count = 0;
    function<void(int, int, long long)> goBack = [&](int i, int j, long long x) {
        if (i + j == half) {
            if (meetingCellTwice) x ^= a[i][j];
            auto it = forward[i].find(x ^ k);
            if (it != forward[i].end()) count += it->second;
            return;
        }
        x ^= a[i][j];
        if (i > 0) goBack(i - 1, j, x);
        if (j > 0) goBack(i, j - 1, x);
    };
    goBack(n - 1, m - 1, 0);
    return count;
}
long long bruteXor(const Grid& a, long long k) {
    int n = a.size(), m = a[0].size();
    long long count = 0;
    function<void(int, int, long long)> walk = [&](int i, int j, long long x) {
        x ^= a[i][j];
        if (i == n - 1 && j == m - 1) { count += x == k; return; }
        if (i + 1 < n) walk(i + 1, j, x);
        if (j + 1 < m) walk(i, j + 1, x);
    };
    walk(0, 0, 0);
    return count;
}
// paths whose cells all have different values: the whole path must be checked, not each half alone
long long bruteDistinct(const Grid& a) {
    int n = a.size(), m = a[0].size();
    long long count = 0;
    vector<long long> seen;
    function<void(int, int)> walk = [&](int i, int j) {
        if (find(seen.begin(), seen.end(), a[i][j]) != seen.end()) return;
        seen.push_back(a[i][j]);
        if (i == n - 1 && j == m - 1) count++;
        else {
            if (i + 1 < n) walk(i + 1, j);
            if (j + 1 < m) walk(i, j + 1);
        }
        seen.pop_back();
    };
    walk(0, 0);
    return count;
}
// each half checked alone for repeated values, then the two counts joined at the meeting cell: repeats across the cut are missed
long long halvesDistinct(const Grid& a) {
    int n = a.size(), m = a[0].size(), half = (n + m - 2) / 2;
    vector<long long> forward(n, 0), backward(n, 0);
    vector<long long> seen;
    function<void(int, int)> goForward = [&](int i, int j) {
        if (find(seen.begin(), seen.end(), a[i][j]) != seen.end()) return;
        seen.push_back(a[i][j]);
        if (i + j == half) forward[i]++;
        else {
            if (i + 1 < n) goForward(i + 1, j);
            if (j + 1 < m) goForward(i, j + 1);
        }
        seen.pop_back();
    };
    goForward(0, 0);
    function<void(int, int)> goBack = [&](int i, int j) {
        if (find(seen.begin(), seen.end(), a[i][j]) != seen.end()) return;
        seen.push_back(a[i][j]);
        if (i + j == half) backward[i]++;
        else {
            if (i > 0) goBack(i - 1, j);
            if (j > 0) goBack(i, j - 1);
        }
        seen.pop_back();
    };
    goBack(n - 1, m - 1);
    long long count = 0;
    for (int i = 0; i < n; i++) count += forward[i] * backward[i];
    return count;
}
int main() {
    // P1: the paths of [[1, 2], [3, 4]] with xor 7. Brute: both paths. Method: cut after one step.
    Grid g1 = {{1, 2}, {3, 4}};
    cout << "P1 brute=" << bruteXor(g1, 7) << " method=" << halves(g1, 7, false) << '\n';
    // P2: the paths of a 3 x 3 grid with xor 1.
    Grid g2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "P2 brute=" << bruteXor(g2, 1) << " method=" << halves(g2, 1, false) << '\n';
    // N1: the same 2 x 2 grid and 7, but the meeting cell is xored into both halves, so it cancels.
    cout << "N1 brute=" << bruteXor(g1, 7) << " method=" << halves(g1, 7, true) << '\n';
    // N2: the paths of a 2 x 3 grid whose cell values are all different.
    Grid g3 = {{1, 2, 3}, {3, 1, 4}};
    cout << "N2 brute=" << bruteDistinct(g3) << " method=" << halvesDistinct(g3) << '\n';
}
