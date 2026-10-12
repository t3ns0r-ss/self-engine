#include <bits/stdc++.h>
using namespace std;

/*
Problem: start with the array of n ones. One move chooses an index i and sets a_i to the current sum of the whole array. Can the given target
array (n up to 5·10^4, values up to 10^9) be reached?
Input: n, then the target values.
Output: YES or NO.
*/

// snippet:begin
// Work backwards. The last move wrote the sum of the array before it, which is larger than every other element, so the largest element m was
// the last one written; undoing it restores m - rest, where rest is the sum of the others. Repeat until all elements are 1.
// If m % rest is used instead of m - rest, the repeated undoing of the same index is done in one step.
bool reachable(const vector<long long>& target) {
    int n = target.size();
    if (n == 1) return target[0] == 1;
    priority_queue<long long> heap(target.begin(), target.end());
    long long sum = accumulate(target.begin(), target.end(), 0LL);
    while (heap.top() > 1) {
        long long m = heap.top();
        heap.pop();
        long long rest = sum - m;
        if (rest == 1) return true;     // [m, 1, ...] goes down to all ones by steps of 1
        if (m <= rest || m % rest == 0) return false;
        long long old = m % rest;       // after undoing as many times as possible
        sum = rest + old;
        heap.push(old);
    }
    return true;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << (reachable(a) ? "YES" : "NO") << "\n";
}
