#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.2. The number of non-empty windows with sum at most K (non-negative values):
// each right end r adds r - l + 1, the number of valid left ends.
long long countWindows(const vector<long long>& a, long long K) {
    long long sum = 0, total = 0;
    int l = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > K) sum -= a[l++];
        total += r - l + 1;
    }
    return total;
}
// snippet:end

int main() {
    cout << "3 1 2 1 4 1, sum at most 5: " << countWindows({3, 1, 2, 1, 4, 1}, 5) << " windows\n";
    cout << "1 1 1, sum at most 3: " << countWindows({1, 1, 1}, 3) << " windows\n";
    cout << "1 1 1, sum at most 1: " << countWindows({1, 1, 1}, 1) << " windows\n";
    mt19937 rng(2);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8 + 1;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 5;
        long long K = rng() % 9, count = 0;
        for (int l = 0; l < n; l++) for (int r = l, s = 0; r < n; r++) { s += a[r]; count += s <= K; }
        if (count != countWindows(a, K)) return 1;
    }
}
