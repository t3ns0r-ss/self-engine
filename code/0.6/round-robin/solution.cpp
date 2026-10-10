/*
Problem: n tasks wait in a queue in order 1..n; task i needs t_i units of work. The worker takes the
task at the front, works on it for up to Q units, and puts it at the back if it is not finished.
Print the tasks in the order they finish.
Input: n Q (1 <= n <= 10^5, 1 <= Q <= 10^9), then t_1 .. t_n (1 <= t_i <= 10^9), with sum(t_i)/Q <= 10^6.
Output: the task numbers in finishing order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.6 (queues). Tasks wait in order; the worker gives each at most Q units and sends an unfinished task
// to the back. Returns the task numbers in finishing order.
vector<int> finishOrder(const vector<long long>& t, long long Q) {
    queue<pair<int, long long>> q;  // (task number, remaining work); the front is the oldest
    for (int i = 0; i < (int)t.size(); i++) q.push({i + 1, t[i]});
    vector<int> order;
    while (!q.empty()) {
        auto [id, rest] = q.front();
        q.pop();
        if (rest <= Q) order.push_back(id);
        else q.push({id, rest - Q});  // back of the queue: first in, first out
    }
    return order;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long Q;
    cin >> n >> Q;
    vector<long long> t(n);
    for (auto& x : t) cin >> x;
    vector<int> order = finishOrder(t, Q);
    for (int i = 0; i < n; i++) cout << order[i] << (i + 1 < n ? ' ' : '\n');
}
