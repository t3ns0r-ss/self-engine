/*
Problem: bars of width 1 and heights h_1 .. h_n stand side by side; print the largest area of a
rectangle that fits under them.
Input: n (1 <= n <= 2*10^5), then h_1 .. h_n (0 <= h_i <= 10^9).
Output: the largest area.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> h(n);
    for (auto& x : h) cin >> x;
    vector<int> L(n), R(n), st;  // nearest strictly lower bar on each side
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.back()] >= h[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.back()] >= h[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long best = 0;  // up to 2*10^5 * 10^9
    for (int i = 0; i < n; i++) best = max(best, h[i] * (R[i] - L[i] - 1));  // Theorem 1.6.2, part 3
    cout << best << "\n";
}
