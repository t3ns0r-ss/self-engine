/*
Problem: AtCoder ABC 120 D, Decayed Bridges.
Input: N M, then M lines "A B": a bridge between islands A and B; the bridges collapse in the order they are listed.
Output: for i = 1..M, the number of pairs of islands that cannot reach each other just after the i-th bridge collapses.
*/
#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (parent[x] != x) parent[x] = parent[parent[x]], x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

// snippet:begin
// Example 2. Add the bridges back from the last to the first; before adding the i-th, the number of linked pairs is known.
vector<long long> inconvenience(int n, const vector<pair<int, int>>& bridges) {
    int m = bridges.size();
    vector<long long> answer(m);
    Dsu dsu(n + 1);
    long long linked = 0, total = 1LL * n * (n - 1) / 2;
    for (int i = m - 1; i >= 0; i--) {
        answer[i] = total - linked;  // all bridges i+1..m-1 are in place: the state just after the i-th (counting from 1) collapses
        int a = dsu.find(bridges[i].first), b = dsu.find(bridges[i].second);
        if (a != b) linked += 1LL * dsu.size[a] * dsu.size[b], dsu.unite(a, b);
    }
    return answer;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> bridges(m);
    for (auto& b : bridges) cin >> b.first >> b.second;
    for (long long x : inconvenience(n, bridges)) cout << x << "\n";
}
