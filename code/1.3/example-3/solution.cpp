/*
Problem: LeetCode Container With Most Water. Choose two lines i < j to maximise (j - i) * min(h[i], h[j]).
Input (our format; LeetCode passes the array to a function): n, then n heights (2 <= n <= 10^5, 0 <= h <= 10^4).
Output: the largest area.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;

    int l = 0, r = n - 1;
    long long best = 0;  // width 10^5 times height 10^4 = 10^9 fits int, but long long costs nothing
    while (l < r) {
        best = max(best, (long long)(r - l) * min(h[l], h[r]));
        if (h[l] <= h[r]) l++;  // h[l] is the shorter side: no container using l can do better
        else r--;               // h[r] is the shorter side
    }
    cout << best << "\n";
}
