#include <bits/stdc++.h>
using namespace std;

// the walk back from the end of a table filled forward: takes the last position first when taking it still reaches the optimum
vector<int> walkBack(const vector<long long>& a) {
    int n = a.size();
    vector<long long> pre(n + 2, 0);
    for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], (i >= 2 ? pre[i - 2] : 0) + a[i - 1]);
    vector<int> chosen;
    for (int i = n; i >= 1;) {
        if (pre[i] == (i >= 2 ? pre[i - 2] : 0) + a[i - 1]) chosen.push_back(i), i -= 2;
        else i -= 1;
    }
    reverse(chosen.begin(), chosen.end());
    return chosen;
}
// the walk forward over the suffix table: takes the first position whenever taking it still reaches the optimum
vector<int> walkForward(const vector<long long>& a) {
    int n = a.size();
    vector<long long> best(n + 2, 0);
    for (int i = n - 1; i >= 0; i--) best[i] = max(best[i + 1], a[i] + best[i + 2]);
    vector<int> chosen;
    for (int i = 0; i < n;) {
        if (a[i] + best[i + 2] == best[i]) chosen.push_back(i + 1), i += 2;
        else i += 1;
    }
    return chosen;
}
string text(const vector<int>& v) {
    string s;
    for (size_t i = 0; i < v.size(); i++) s += (i ? "-" : "") + to_string(v[i]);
    return s;
}
vector<int> frogPath(const vector<int>& h, int k) {
    int n = h.size();
    vector<long long> best(n, LLONG_MAX);
    vector<int> from(n, -1);
    best[0] = 0;
    for (int i = 1; i < n; i++) for (int j = max(0, i - k); j < i; j++) if (best[j] + abs(h[i] - h[j]) < best[i]) best[i] = best[j] + abs(h[i] - h[j]), from[i] = j;
    vector<int> path;
    for (int i = n - 1; i != -1; i = from[i]) path.push_back(i + 1);
    reverse(path.begin(), path.end());
    return path;
}
int main() {
    // P1: the stones on the cheapest path for the heights 10 30 40 20. Brute: the only cheapest path, found by listing the paths.
    vector<int> h = {10, 30, 40, 20};
    vector<int> bestPath;
    long long bestCost = LLONG_MAX;
    for (int mask = 0; mask < 4; mask++) {  // which of the middle stones 2 and 3 are visited
        vector<int> path = {1};
        if (mask & 1) path.push_back(2);
        if (mask & 2) path.push_back(3);
        path.push_back(4);
        long long cost = 0;
        bool ok = true;
        for (size_t i = 1; i < path.size(); i++) { if (path[i] - path[i - 1] > 2) ok = false; cost += abs(h[path[i] - 1] - h[path[i - 1] - 1]); }
        if (ok && cost < bestCost) bestCost = cost, bestPath = path;
    }
    cout << "P1 brute=" << text(bestPath) << " method=" << text(frogPath(h, 2)) << '\n';
    // P2: the lexicographically smallest positions with the largest non-adjacent sum in 5 1 5.
    vector<long long> a = {5, 1, 5};
    cout << "P2 brute=" << "1-3" << " method=" << text(walkForward(a)) << '\n';
    // N1: the same question for 2 2 2 2 (the best sum 4), walking back from the end of a table filled forward.
    vector<long long> b = {2, 2, 2, 2};
    cout << "N1 brute=" << "1-3" << " method=" << text(walkBack(b)) << '\n';
}
