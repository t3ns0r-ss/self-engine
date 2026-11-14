#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.6. L[i] = the length of the longest increasing subsequence ending at i, C[i] = the number of them. C[i] adds
// C[j] over the earlier smaller a[j] with L[j] = L[i] - 1; the answer adds C[i] over the positions with L[i] = max L.
pair<vector<int>, vector<long long>> lengthsAndCounts(const vector<int>& a) {
    int n = a.size();
    vector<int> L(n, 1);
    vector<long long> C(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[i]) continue;
            if (L[j] + 1 > L[i]) L[i] = L[j] + 1, C[i] = C[j];
            else if (L[j] + 1 == L[i]) C[i] += C[j];
        }
    return {L, C};
}
// snippet:end

long long answer(const vector<int>& a) {
    auto [L, C] = lengthsAndCounts(a);
    int best = *max_element(L.begin(), L.end());
    long long total = 0;
    for (size_t i = 0; i < a.size(); i++)
        if (L[i] == best) total += C[i];
    return total;
}

int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    auto [L, C] = lengthsAndCounts(a);
    cout << "L:";
    for (int x : L) cout << ' ' << x;
    cout << "\nC:";
    for (long long x : C) cout << ' ' << x;
    cout << "\nlongest increasing subsequences: " << answer(a) << '\n';
    mt19937 rng(34);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 11;
        vector<int> b(n);
        for (int& x : b) x = rng() % 6;
        int best = 0;
        long long ways = 0;
        for (int mask = 1; mask < (1 << n); mask++) {
            int last = INT_MIN, len = 0;
            bool ok = true;
            for (int i = 0; i < n && ok; i++)
                if (mask >> i & 1) {
                    if (b[i] <= last) ok = false;
                    last = b[i], len++;
                }
            if (!ok) continue;
            if (len > best) best = len, ways = 1;
            else if (len == best) ways++;
        }
        if (answer(b) != ways) return 1;
    }
}
