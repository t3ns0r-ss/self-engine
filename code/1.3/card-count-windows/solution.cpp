#include <bits/stdc++.h>
using namespace std;

long long countAtMost(const vector<int>& a, int K) {
    int sum = 0, l = 0;
    long long total = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > K && l <= r) sum -= a[l++];
        total += r - l + 1;
    }
    return total;
}

int main() {
    // P1: the windows of 3 1 2 1 4 1 with sum at most 5. Brute: all 21 windows. Method: r - l + 1 per right end.
    vector<int> a = {3, 1, 2, 1, 4, 1};
    int brute = 0;
    for (int l = 0; l < 6; l++) for (int r = l, s = 0; r < 6; r++) { s += a[r]; brute += s <= 5; }
    cout << "P1 brute=" << brute << " method=" << countAtMost(a, 5) << '\n';
    // N1: the windows of 2 -1 1 with sum at most 1, with a negative value in the array.
    vector<int> b = {2, -1, 1};
    brute = 0;
    for (int l = 0; l < 3; l++) for (int r = l, s = 0; r < 3; r++) { s += b[r]; brute += s <= 1; }
    cout << "N1 brute=" << brute << " method=" << countAtMost(b, 1) << '\n';
    // N2: the windows of 3 1 2 1 4 1 with sum at least 5, counted with the "at most 5" loop.
    brute = 0;
    for (int l = 0; l < 6; l++) for (int r = l, s = 0; r < 6; r++) { s += a[r]; brute += s >= 5; }
    cout << "N2 brute=" << brute << " method=" << countAtMost(a, 5) << '\n';
}
