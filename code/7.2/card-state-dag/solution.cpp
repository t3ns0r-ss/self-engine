#include <bits/stdc++.h>
using namespace std;

// method: the fewest steps from x to y when only moves that make the number smaller are used (then a memoised recursion is enough);
// brute: breadth-first search over all the numbers 1 .. 60 with the moves x - 1, x + 1, x / 5 (if divisible), x / 11 (if divisible).
long long days(long long n, map<long long, long long>& memo) {
    if (n <= 1) return n;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;
    return memo[n] = 1 + min(n % 2 + days(n / 2, memo), n % 3 + days(n / 3, memo));
}
int bruteDays(int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[n] = 0, q.push(n);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == 0) return dist[0];
        vector<int> to = {v - 1};
        if (v % 2 == 0) to.push_back(v / 2);
        if (v % 3 == 0) to.push_back(v / 3);
        for (int u : to)
            if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
    }
    return -1;
}
int bfs(int x, int y) {
    vector<int> dist(61, -1);
    queue<int> q;
    dist[x] = 0, q.push(x);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        vector<int> to = {v - 1, v + 1};
        if (v % 5 == 0) to.push_back(v / 5);
        if (v % 11 == 0) to.push_back(v / 11);
        for (int u : to)
            if (u >= 1 && u <= 60 && dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
    }
    return dist[y];
}
int decreasingOnly(int x, int y) {  // moves that make x smaller, as a memoised recursion; -1 if y cannot be reached
    map<int, int> memo;
    function<int(int)> go = [&](int v) -> int {
        if (v == y) return 0;
        if (v < y) return -1;
        auto it = memo.find(v);
        if (it != memo.end()) return it->second;
        int best = -1;
        vector<int> to = {v - 1};
        if (v % 5 == 0) to.push_back(v / 5);
        if (v % 11 == 0) to.push_back(v / 11);
        for (int u : to) {
            int r = go(u);
            if (r >= 0 && (best < 0 || r + 1 < best)) best = r + 1;
        }
        return memo[v] = best;
    };
    return go(x);
}

int main() {
    for (int n : {10, 6}) {
        map<long long, long long> memo;
        cout << (n == 10 ? "P1" : "P2") << " brute=" << bruteDays(n) << " method=" << days(n, memo) << "\n";
    }
    // N1: from 1 to 2 the only way is to go up, which a recursion on smaller numbers never tries.
    cout << "N1 brute=" << bfs(1, 2) << " method=" << decreasingOnly(1, 2) << "\n";
}
