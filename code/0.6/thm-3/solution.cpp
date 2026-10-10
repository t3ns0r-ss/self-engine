#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.3. The number of pairs i < j with a_i = a_j: each element adds the count of its value read
// just before it is incremented.
long long equalPairs(const vector<int>& a) {
    map<int, int> cnt;
    long long pairs = 0;
    for (int x : a) {
        pairs += cnt[x];
        cnt[x]++;
    }
    return pairs;
}
// snippet:end

int main() {
    for (vector<int> a : {vector<int>{3, 1, 3, 3}, vector<int>{1, 2, 3}, vector<int>{5, 5, 5, 5}}) {
        cout << "equal pairs in";
        for (int x : a) cout << ' ' << x;
        cout << ": " << equalPairs(a) << '\n';
    }
    mt19937 rng(2);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 9;
        vector<int> b(n);
        for (int& x : b) x = rng() % 4;
        long long brute = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) brute += b[i] == b[j];
        if (brute != equalPairs(b)) return 1;
    }
}
