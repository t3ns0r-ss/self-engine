/*
Problem: LeetCode Container With Most Water. Choose two lines i < j to maximise (j - i) * min(h[i], h[j]).
Input (our format; LeetCode passes the array to a function): n, then n heights (2 <= n <= 10^5, 0 <= h <= 10^4).
Output: the largest area.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The largest area of a container made of two lines: move the pointer at the shorter line inwards.
long long mostWater(const vector<int>& h) {
    int l = 0, r = h.size() - 1;
    long long best = 0;
    while (l < r) {
        best = max(best, (long long)(r - l) * min(h[l], h[r]));
        if (h[l] <= h[r]) l++;  // h[l] is the shorter side: no container using l can do better
        else r--;               // h[r] is the shorter side
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    cout << mostWater(h) << "\n";
}
