#include <bits/stdc++.h>
using namespace std;

// brute: can 1 ... n be split into `parts` sets of equal sum? (a search over assignments)
bool bruteSplit(int n, int parts) {
    int total = n * (n + 1) / 2;
    if (total % parts) return false;
    int target = total / parts;
    vector<int> sums(parts, 0);
    function<bool(int)> go = [&](int j) {
        if (j == 0) return true;
        for (int i = 0; i < parts; i++) {
            if (sums[i] + j > target) continue;
            sums[i] += j;
            if (go(j - 1)) return true;
            sums[i] -= j;
            if (sums[i] == 0) break;  // equal empty sets are the same
        }
        return false;
    };
    return go(n);
}
// method: the greedy of Theorem 7.7.3 when the sum is even; and the necessary condition "the sum is divisible by 3" taken as sufficient for 3 parts.
vector<int> halfOfSum(int n) {
    long long total = (long long)n * (n + 1) / 2;
    if (total % 2 != 0) return {};
    long long missing = total / 2;
    vector<int> first;
    for (int j = n; j >= 1; j--)
        if (j <= missing) first.push_back(j), missing -= j;
    return first;
}
int main() {
    cout << "P1 brute=" << (bruteSplit(8, 2) ? "yes" : "no") << " method=" << (!halfOfSum(8).empty() ? "yes" : "no") << "\n";
    cout << "P2 brute=" << (bruteSplit(6, 2) ? "yes" : "no") << " method=" << (!halfOfSum(6).empty() ? "yes" : "no") << "\n";
    cout << "N1 brute=" << (bruteSplit(3, 3) ? "yes" : "no") << " method=" << ((3 * 4 / 2) % 3 == 0 ? "yes" : "no") << "\n";
    // N2: can the numbers 1, 2, 5 be split into two sets of equal sum? (the parity of the total is the only condition checked)
    vector<int> a = {1, 2, 5};
    int total = 8;
    bool exists = false;
    for (int mask = 0; mask < 8; mask++) {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            if (mask >> i & 1) sum += a[i];
        exists = exists || sum * 2 == total;
    }
    cout << "N2 brute=" << (exists ? "yes" : "no") << " method=" << (total % 2 == 0 ? "yes" : "no") << "\n";
}
