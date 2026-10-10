#include <bits/stdc++.h>
using namespace std;

int longestAtMost(const vector<int>& a, int K) {
    int sum = 0, l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > K && l <= r) sum -= a[l++];
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    // P1: the longest window of 3 1 2 1 4 1 with sum at most 5. Brute: all windows. Method: the shrinking window.
    vector<int> a = {3, 1, 2, 1, 4, 1};
    int brute = 0;
    for (int l = 0; l < 6; l++) for (int r = l, s = 0; r < 6; r++) { s += a[r]; if (s <= 5) brute = max(brute, r - l + 1); }
    cout << "P1 brute=" << brute << " method=" << longestAtMost(a, 5) << '\n';
    // N1: the longest window of 5 -3 1 with sum at most 3, where a negative value breaks the shrinking.
    vector<int> b = {5, -3, 1};
    brute = 0;
    for (int l = 0; l < 3; l++) for (int r = l, s = 0; r < 3; r++) { s += b[r]; if (s <= 3) brute = max(brute, r - l + 1); }
    cout << "N1 brute=" << brute << " method=" << longestAtMost(b, 3) << '\n';
    // N2: the longest window of 0 0 0 5 with sum EXACTLY 3, answered by the "at most 3" window.
    vector<int> c = {0, 0, 0, 5};
    brute = 0;
    for (int l = 0; l < 4; l++) for (int r = l, s = 0; r < 4; r++) { s += c[r]; if (s == 3) brute = max(brute, r - l + 1); }
    cout << "N2 brute=" << brute << " method=" << longestAtMost(c, 3) << '\n';
}
