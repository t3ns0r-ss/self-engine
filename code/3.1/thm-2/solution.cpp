#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.2. Canonical order: the next index is larger than the last one taken, and inside one loop a value equal to
// the previous try is skipped. Every distinct sub-multiset of the sorted values is produced exactly once.
vector<vector<int>> distinctSubsets(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size();
    vector<vector<int>> found;
    vector<int> chosen;
    function<void(int)> rec = [&](int start) {
        found.push_back(chosen);
        for (int i = start; i < n; i++) {
            if (i > start && a[i] == a[i - 1]) continue;
            chosen.push_back(a[i]);
            rec(i + 1);
            chosen.pop_back();
        }
    };
    rec(0);
    return found;
}
// snippet:end

int main() {
    auto found = distinctSubsets({1, 2, 2});
    cout << "distinct sub-multisets of 1 2 2: " << found.size() << '\n';
    for (auto& s : found) {
        cout << '{';
        for (size_t i = 0; i < s.size(); i++) cout << (i ? ", " : "") << s[i];
        cout << "}\n";
    }
    mt19937 rng(9);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 9;
        vector<int> a(n);
        for (int& x : a) x = 1 + rng() % 4;
        set<vector<int>> want;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> s;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s.push_back(a[i]);
            sort(s.begin(), s.end());
            want.insert(s);
        }
        auto got = distinctSubsets(a);
        for (auto& s : got) if (!is_sorted(s.begin(), s.end())) return 1;
        if (set<vector<int>>(got.begin(), got.end()) != want || got.size() != want.size()) return 1;
    }
}
