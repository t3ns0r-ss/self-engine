/*
Problem: the sum of the minimum of every subarray of an array.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^6).
Output: the sum (at most 10^6 * n(n+1)/2, about 2*10^16).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // L[i]: previous position with a smaller value (strictly), or -1
    // R[i]: next position with a smaller or equal value, or n   (ties broken on one side only)
    vector<int> L(n), R(n), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long total = 0;
    for (int i = 0; i < n; i++) total += a[i] * (i - L[i]) * (R[i] - i);  // Theorem 1.6.2
    cout << total << "\n";
}
