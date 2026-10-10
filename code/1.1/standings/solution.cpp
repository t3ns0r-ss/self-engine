/*
Problem: contestant i (numbered 1..n in input order) solved s_i problems with penalty p_i. Print the
contestants ranked by more problems first, then by smaller penalty, then by smaller number.
Input: n (1 <= n <= 2*10^5), then n lines "s_i p_i" (0 <= s_i <= 100, 0 <= p_i <= 10^9).
Output: the contestant numbers in ranked order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.3. Order contestants by more problems solved, then smaller penalty, then smaller id.
struct Contestant {
    int solved, penalty, id;
};

vector<int> standings(vector<Contestant> c) {
    // true when x must come before y; three keys in turn
    auto before = [](const Contestant& x, const Contestant& y) {
        if (x.solved != y.solved) return x.solved > y.solved;  // more solved first
        if (x.penalty != y.penalty) return x.penalty < y.penalty;
        return x.id < y.id;  // the statement's last tie-break; sort is not stable
    };
    sort(c.begin(), c.end(), before);
    vector<int> order;
    for (auto& x : c) order.push_back(x.id);
    return order;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Contestant> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i].solved >> c[i].penalty;
        c[i].id = i + 1;
    }
    vector<int> order = standings(c);
    for (int i = 0; i < n; i++) cout << order[i] << (i + 1 < n ? ' ' : '\n');
}
