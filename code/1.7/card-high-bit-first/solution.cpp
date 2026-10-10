#include <bits/stdc++.h>
using namespace std;

int greedyAnd(const vector<int>& a, int top, int need) {
    int ans = 0;
    for (int b = top; b >= 0; b--) {
        int want = ans | (1 << b), c = 0;
        for (int x : a) c += (x & want) == want;
        if (c >= need) ans = want;
    }
    return ans;
}

int main() {
    // P1 and P2: the largest AND of a pair in 5 6 3 and in 1 2. Brute: all pairs. Method: the highest bit first.
    vector<vector<int>> sets = {{5, 6, 3}, {1, 2}};
    for (int s = 0; s < 2; s++) {
        int brute = 0;
        for (size_t i = 0; i < sets[s].size(); i++) for (size_t j = i + 1; j < sets[s].size(); j++) brute = max(brute, sets[s][i] & sets[s][j]);
        cout << "P" << s + 1 << " brute=" << brute << " method=" << greedyAnd(sets[s], 29, 2) << '\n';
    }
    // N1: the same for 5 6 3, but a bit is kept when ONE value (not two) has all the decided bits.
    cout << "N1 brute=4 method=" << greedyAnd({5, 6, 3}, 29, 1) << '\n';
    // N2: the largest AND of the pair 2^25 + 5 and 2^25 + 3, deciding only the lowest 20 bits.
    vector<int> big = {(1 << 25) + 5, (1 << 25) + 3};
    cout << "N2 brute=" << (big[0] & big[1]) << " method=" << greedyAnd(big, 19, 2) << '\n';
}
