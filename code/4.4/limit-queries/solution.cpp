/*
Problem: roads with height limits.
Input: n m q, then m lines "a b w": a two-way road with limit w; then q lines "s t L".
Output: for each question, YES if some trip from s to t uses only roads with w <= L, otherwise NO.
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
// Theorem 4.4.6. Offline: sort roads and questions by the limit, add the roads up to each limit, then ask whether s and t are linked.
vector<bool> tripsUnderLimit(int n, vector<array<long long, 3>> roads, const vector<array<long long, 3>>& questions) {
    sort(roads.begin(), roads.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    vector<int> order(questions.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) { return questions[x][2] < questions[y][2]; });
    Dsu dsu(n + 1);
    vector<bool> answer(questions.size());
    size_t next = 0;
    for (int i : order) {
        auto [s, t, limit] = questions[i];
        while (next < roads.size() && roads[next][2] <= limit) dsu.unite(roads[next][0], roads[next][1]), next++;  // every road allowed so far
        answer[i] = dsu.find(s) == dsu.find(t);
    }
    return answer;
}
// snippet:end

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<long long, 3>> roads(m), questions(q);
    for (auto& r : roads) cin >> r[0] >> r[1] >> r[2];
    for (auto& x : questions) cin >> x[0] >> x[1] >> x[2];
    auto answer = tripsUnderLimit(n, roads, questions);
    for (int i = 0; i < q; i++) cout << (answer[i] ? "YES" : "NO") << "\n";
}
