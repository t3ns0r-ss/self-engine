#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.1. The XOR of a list is the XOR of the values that appear an odd number of times: a value appearing twice
// cancels. The XOR of 0..n has a pattern of period 4.
int xorAll(const vector<int>& a) {
    int result = 0;
    for (int x : a) result ^= x;
    return result;
}
long long xorUpTo(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}
// snippet:end

int main() {
    cout << "XOR of 4 7 4 2 7: " << xorAll({4, 7, 4, 2, 7}) << '\n';
    for (int n : {4, 5, 6, 7}) cout << "XOR of 0.." << n << ": " << xorUpTo(n) << '\n';
    for (int n = 0; n <= 200; n++) {
        long long x = 0;
        for (int i = 0; i <= n; i++) x ^= i;
        if (x != xorUpTo(n)) return 1;
    }
    mt19937 rng(1);
    for (int round = 0; round < 300; round++) {
        vector<int> a(rng() % 8);
        map<int, int> cnt;
        for (int& v : a) v = rng() % 6, cnt[v]++;
        int odd = 0;
        for (auto [v, c] : cnt) if (c % 2) odd ^= v;
        if (odd != xorAll(a)) return 1;
    }
}
