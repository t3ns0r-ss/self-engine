#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.5. Halve the largest number (rounding down), k times; the sum of what remains.
long long halveLargest(const vector<long long>& a, int k) {
    priority_queue<long long> pq(a.begin(), a.end());  // top() is the largest
    for (int i = 0; i < k; i++) {
        long long x = pq.top();
        pq.pop();
        pq.push(x / 2);
    }
    long long sum = 0;
    for (; !pq.empty(); pq.pop()) sum += pq.top();
    return sum;
}
// snippet:end

int main() {
    cout << "8 3 5, halve the largest 3 times: sum " << halveLargest({8, 3, 5}, 3) << '\n';
    cout << "8 3 5, halve the largest 0 times: sum " << halveLargest({8, 3, 5}, 0) << '\n';
    cout << "10, halve the largest 3 times: sum " << halveLargest({10}, 3) << '\n';
    mt19937 rng(6);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 5 + 1, k = rng() % 6;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 30;
        vector<long long> b = a;
        for (int i = 0; i < k; i++) *max_element(b.begin(), b.end()) /= 2;
        if (accumulate(b.begin(), b.end(), 0LL) != halveLargest(a, k)) return 1;
    }
}
