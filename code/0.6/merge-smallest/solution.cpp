/*
Problem: n piles; repeatedly merge the two smallest piles into one, paying their total size, until one
pile is left. Print the total cost.
Input: n (1 <= n <= 2*10^5), then the sizes (1 <= a_i <= 10^9).
Output: the total cost.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.5. Merge the two smallest piles again and again, paying their total; the minimum total cost.
long long mergeCost(const vector<long long>& a) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(a.begin(), a.end());  // top() is the smallest
    long long cost = 0;
    while (pq.size() > 1) {
        long long x = pq.top();
        pq.pop();
        long long y = pq.top();
        pq.pop();
        cost += x + y;
        pq.push(x + y);
    }
    return cost;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << mergeCost(a) << "\n";
}
