#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.7.4. A permutation p of 1 ... n is sorted by n - c swaps, where c is its number of cycles, and no sequence of swaps is shorter.
// For i = 1, 2, ...: if the value i is not at the position i, swap it into place. The positions below i are never touched again.
vector<pair<int, int>> sortBySwaps(vector<int> p) {  // p[0] is the position 1; returns the swapped positions (from 1)
    int n = p.size();
    vector<int> where(n + 1);
    for (int i = 0; i < n; i++) where[p[i]] = i;
    vector<pair<int, int>> swaps;
    for (int i = 0; i < n; i++) {
        if (p[i] == i + 1) continue;
        int j = where[i + 1];
        swap(p[i], p[j]);
        where[p[j]] = j;
        where[p[i]] = i;
        swaps.push_back({i + 1, j + 1});
    }
    return swaps;
}
// snippet:end

int cycles(const vector<int>& p) {
    int n = p.size(), c = 0;
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++)
        if (!seen[i]) {
            c++;
            for (int j = i; !seen[j]; j = p[j] - 1) seen[j] = true;
        }
    return c;
}

int main() {
    for (vector<int> p : {vector<int>{2, 3, 1}, vector<int>{2, 1, 4, 3}, vector<int>{1, 2, 3}}) {
        cout << "p =";
        for (int x : p) cout << " " << x;
        cout << ":";
        auto swaps = sortBySwaps(p);
        if (swaps.empty()) cout << " no swaps";
        for (auto [a, b] : swaps) cout << " (" << a << "," << b << ")";
        cout << "\n";
    }
    // Check (not printed): all permutations of up to 7 elements: the swaps sort the array, their number is n - c, and a search by swaps finds
    // no shorter way.
    for (int n = 1; n <= 7; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 1);
        map<vector<int>, int> dist;  // distance to the sorted permutation (swaps are reversible)
        vector<int> target = p;
        queue<vector<int>> q;
        dist[target] = 0;
        q.push(target);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++) {
                    auto next = cur;
                    swap(next[i], next[j]);
                    if (!dist.count(next)) dist[next] = dist[cur] + 1, q.push(next);
                }
        }
        do {
            auto swaps = sortBySwaps(p);
            auto sorted = p;
            for (auto [a, b] : swaps) swap(sorted[a - 1], sorted[b - 1]);
            if (!is_sorted(sorted.begin(), sorted.end())) return 1;
            if ((int)swaps.size() != n - cycles(p) || (int)swaps.size() != dist[p]) return 1;
        } while (next_permutation(p.begin(), p.end()));
    }
}
