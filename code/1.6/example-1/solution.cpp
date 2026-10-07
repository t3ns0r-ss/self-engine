/*
Problem: ABC 372 D Buildings. N buildings with distinct heights H_1 .. H_N; for each i, count the
j > i such that no building between i and j is taller than building j.
Input: N (1 <= N <= 2*10^5), then H_1 .. H_N (a permutation of 1 .. N).
Output: c_1 .. c_N.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> c(n), st;  // st: buildings visible from just left of position i + 1, nearest on top
    for (int i = n - 1; i >= 0; i--) {
        c[i] = st.size();
        while (!st.empty() && h[st.back()] < h[i]) st.pop_back();  // hidden behind building i
        st.push_back(i);
    }
    for (int i = 0; i < n; i++) cout << c[i] << (i + 1 < n ? ' ' : '\n');
}
