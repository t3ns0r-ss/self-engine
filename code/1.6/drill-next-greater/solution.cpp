/*
Drill (about 4 minutes). For every i print the value of the first element to the right of position i that is strictly
greater than a_i, or -1 if there is none.
Input: n, then a_1..a_n (1 <= a_i <= 10^9), n <= 2*10^5.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Scan from the right. The stack holds candidates in decreasing order; drop the ones that are not greater than a[i].
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), ans(n);
    for (auto& x : a) cin >> x;
    vector<long long> st;  // values, the top is the nearest
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.back() <= a[i]) st.pop_back();
        ans[i] = st.empty() ? -1 : st.back();
        st.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 < n ? ' ' : '\n');
}
// snippet:end
