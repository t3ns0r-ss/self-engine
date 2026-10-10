#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.1.1. st[j][i] = the minimum of a[i .. i + 2^j - 1]; a level j exists while 2^j <= n.
vector<vector<int>> buildLevels(const vector<int>& a) {
    int n = a.size();
    vector<vector<int>> st = {a};  // level 0: blocks of length 1
    for (int j = 1; (1 << j) <= n; j++) {
        int half = 1 << (j - 1);
        st.push_back(vector<int>(n - (1 << j) + 1));
        for (int i = 0; i + (1 << j) <= n; i++)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + half]);  // the two halves of the block
    }
    return st;
}
// snippet:end

static void show(const vector<int>& a) {
    cout << "a =";
    for (int x : a) cout << ' ' << x;
    cout << "\n";
    auto st = buildLevels(a);
    for (int j = 0; j < (int)st.size(); j++) {
        cout << "level " << j << ":";
        for (int x : st[j]) cout << ' ' << x;
        cout << "\n";
    }
}

int main() {
    show({5, 2, 4, 7, 1, 3, 6});
    show({4, 4, 4, 4});
    show({9});
    // Check against: the minimum of the block, on every array of length 1..6 over {1, 2, 3}.
    for (int n = 1; n <= 6; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 3;
        for (int code = 0; code < total; code++) {
            vector<int> a(n);
            for (int i = 0, c = code; i < n; i++, c /= 3) a[i] = c % 3 + 1;
            auto st = buildLevels(a);
            int levels = 1;
            while ((1 << levels) <= n) levels++;
            if ((int)st.size() != levels) return 1;
            for (int j = 0; j < levels; j++) {
                if ((int)st[j].size() != n - (1 << j) + 1) return 1;
                for (int i = 0; i + (1 << j) <= n; i++)
                    if (st[j][i] != *min_element(a.begin() + i, a.begin() + i + (1 << j))) return 1;
            }
        }
    }
}
