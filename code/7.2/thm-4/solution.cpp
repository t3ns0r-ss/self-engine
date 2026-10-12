#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.2.4. The fewest days to eat n oranges: eat one; if n is even eat n / 2; if n is divisible by 3 eat 2n / 3.
// Eating single oranges until n is divisible by 2 (or by 3) and then taking the big step is enough, so
// days(n) = 1 + min(n % 2 + days(n / 2), n % 3 + days(n / 3)). Every call is on a smaller number; each number is computed once.
long long days(long long n, map<long long, long long>& memo) {
    if (n <= 1) return n;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;
    return memo[n] = 1 + min(n % 2 + days(n / 2, memo), n % 3 + days(n / 3, memo));
}
// snippet:end

// The three moves tried one by one with a breadth-first search over the numbers 0 .. n.
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

int main() {
    for (long long n : {10LL, 6LL, 1LL, 2000000000LL}) {
        map<long long, long long> memo;
        long long answer = days(n, memo);
        cout << "n = " << n << ": " << answer << " days, " << memo.size() << " numbers computed\n";
    }
    // Check (not printed): the same as the search for every n from 1 to 3000.
    for (int n = 1; n <= 3000; n++) {
        map<long long, long long> memo;
        if (days(n, memo) != bruteDays(n)) return 1;
    }
}
