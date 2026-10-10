/*
Problem: the sum of the minimum of every subarray of an array.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (1 <= a_i <= 10^6).
Output: the sum (at most 10^6 * n(n+1)/2, about 2*10^16).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.2. Sum of the minimum of every subarray.
long long sumOfMinima(const vector<long long>& a) {
    int n = a.size();
    vector<int> L(n), R(n), st;  // L: previous strictly smaller (or -1); R: next smaller-or-equal (or n)
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
    for (int i = 0; i < n; i++) total += a[i] * (i - L[i]) * (R[i] - i);
    return total;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << sumOfMinima(a) << "\n";
}
