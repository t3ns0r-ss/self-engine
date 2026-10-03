/*
Problem: n piles; repeatedly merge the two smallest piles into one, paying their total size, until one
pile is left. Print the total cost.
Input: n (1 <= n <= 2*10^5), then the sizes (1 <= a_i <= 10^9).
Output: the total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    priority_queue<long long, vector<long long>, greater<long long>> pq;  // top() is the smallest
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        pq.push(a);
    }
    long long cost = 0;  // can reach about 2*10^14 * log n
    while (pq.size() > 1) {
        long long x = pq.top();
        pq.pop();
        long long y = pq.top();
        pq.pop();
        cost += x + y;
        pq.push(x + y);  // each step O(log n) (Theorem 0.6.5)
    }
    cout << cost << "\n";
}
