/*
Problem: for each position of an array, print the position of the next greater element (to the right,
strictly greater) and of the previous greater-or-equal element (to the left), 1-based, 0 if none.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: line 1: next greater positions; line 2: previous greater-or-equal positions.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.1. next[i]: next greater element of i; prev[i]: previous greater-or-equal element. -1 = none.
void scan(const vector<long long>& a, vector<int>& next, vector<int>& prev) {
    int n = a.size();
    next.assign(n, -1), prev.assign(n, -1);
    vector<int> st;  // positions still waiting for a greater value; values never increase upwards
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) {
            next[st.back()] = i;
            st.pop_back();
        }
        if (!st.empty()) prev[i] = st.back();
        st.push_back(i);
    }
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<int> nxt, prv;
    scan(a, nxt, prv);
    for (int i = 0; i < n; i++) cout << nxt[i] + 1 << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << prv[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
