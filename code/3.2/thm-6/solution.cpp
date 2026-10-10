#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.6. Reconstruction: record for each stone the jump that attains the minimum, then walk back from the last
// stone to the first.
vector<int> frogPath(const vector<int>& h, int k) {
    int n = h.size();
    vector<long long> best(n, LLONG_MAX);
    vector<int> from(n, -1);
    best[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = max(0, i - k); j < i; j++)
            if (best[j] + abs(h[i] - h[j]) < best[i]) best[i] = best[j] + abs(h[i] - h[j]), from[i] = j;
    vector<int> path;
    for (int i = n - 1; i != -1; i = from[i]) path.push_back(i + 1);  // 1-based stone numbers
    reverse(path.begin(), path.end());
    return path;
}
// snippet:end

int main() {
    auto path = frogPath({10, 30, 40, 20}, 2);
    cout << "stones on the cheapest path:";
    for (int s : path) cout << ' ' << s;
    cout << '\n';
    mt19937 rng(10);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 9, k = 1 + rng() % 3;
        vector<int> h(n);
        for (int& x : h) x = 1 + rng() % 20;
        auto pth = frogPath(h, k);
        long long cost = 0;
        for (size_t i = 1; i < pth.size(); i++) {
            if (pth[i] - pth[i - 1] > k) return 1;
            cost += abs(h[pth[i] - 1] - h[pth[i - 1] - 1]);
        }
        vector<long long> best(n, LLONG_MAX);
        best[0] = 0;
        for (int i = 1; i < n; i++) for (int j = max(0, i - k); j < i; j++) best[i] = min(best[i], best[j] + abs(h[i] - h[j]));
        if (pth.front() != 1 || pth.back() != n || cost != best[n - 1]) return 1;
    }
}
