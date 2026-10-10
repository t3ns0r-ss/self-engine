#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.4. All sequences c_0 .. c_{L-1} with every c_p in 1..M, by recursion: k^L sequences with k = M.
void rec(int pos, int L, int M, vector<int>& c, vector<vector<int>>& all) {
    if (pos == L) {  // base case: a complete sequence
        all.push_back(c);
        return;
    }
    for (int v = 1; v <= M; v++) {
        c[pos] = v;
        rec(pos + 1, L, M, c, all);
    }
}
// snippet:end

int main() {
    for (auto [L, M] : {pair{2, 3}, pair{3, 2}}) {
        vector<int> c(L);
        vector<vector<int>> all;
        rec(0, L, M, c, all);
        cout << "L = " << L << ", M = " << M << ": " << all.size() << " sequences";
        if (L == 2) {
            cout << ':';
            for (auto& s : all) cout << ' ' << s[0] << s[1];
        }
        cout << '\n';
    }
    for (int L = 1; L <= 5; L++)
        for (int M = 1; M <= 4; M++) {
            vector<int> c(L);
            vector<vector<int>> all;
            rec(0, L, M, c, all);
            if (all.size() != (size_t)pow(M, L) || !is_sorted(all.begin(), all.end()) || set<vector<int>>(all.begin(), all.end()).size() != all.size()) return 1;
        }
}
