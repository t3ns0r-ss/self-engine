#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.3. Every distinct arrangement of a, in increasing order. The loop must start from the sorted sequence.
vector<vector<int>> arrangements(vector<int> a) {
    sort(a.begin(), a.end());
    vector<vector<int>> all;
    do {
        all.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return all;
}
// snippet:end

int main() {
    for (vector<int> a : {vector<int>{1, 2, 3}, vector<int>{1, 1, 2}}) {
        cout << "arrangements of";
        for (int x : a) cout << ' ' << x;
        cout << ':';
        for (auto& s : arrangements(a)) {
            cout << ' ';
            for (int x : s) cout << x;
        }
        cout << '\n';
    }
    mt19937 rng(5);
    for (int round = 0; round < 200; round++) {  // against listing all n^n sequences and keeping the distinct arrangements
        int n = rng() % 5 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 3;
        vector<int> sorted = a;
        sort(sorted.begin(), sorted.end());
        set<vector<int>> want;
        vector<int> idx(n, 0);
        for (long long code = 0; code < (long long)pow(n, n); code++) {
            long long c = code;
            for (int i = 0; i < n; i++) idx[i] = c % n, c /= n;
            set<int> distinct(idx.begin(), idx.end());
            if ((int)distinct.size() != n) continue;
            vector<int> b(n);
            for (int i = 0; i < n; i++) b[i] = sorted[idx[i]];
            want.insert(b);
        }
        auto got = arrangements(a);
        if (set<vector<int>>(got.begin(), got.end()) != want || got.size() != want.size() || !is_sorted(got.begin(), got.end())) return 1;
    }
}
