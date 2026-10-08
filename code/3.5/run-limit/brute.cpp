// Brute force: list all k^n strings as numbers in base k and check the longest run of each.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, r;
    cin >> n >> k >> r;
    long long total = 1, good = 0;
    for (int i = 0; i < n; i++) total *= k;
    for (long long code = 0; code < total; code++) {
        vector<int> s(n);
        long long x = code;
        for (int i = 0; i < n; i++) s[i] = x % k, x /= k;
        int run = 1;
        bool ok = true;
        for (int i = 1; i < n; i++) {
            run = (s[i] == s[i - 1]) ? run + 1 : 1;
            if (run > r) ok = false;
        }
        if (ok) good++;
    }
    cout << good % 1'000'000'007 << "\n";
}
