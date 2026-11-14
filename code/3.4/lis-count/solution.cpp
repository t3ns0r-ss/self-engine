/*
Problem: count the longest strictly increasing subsequences of an array (two subsequences are different when they use different
positions).
Input: n (1 <= n <= 2000), then n integers (|a_i| <= 10^6). The count is promised to fit in 64 bits.
Output: the number of longest strictly increasing subsequences.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.6. L[i] = the length of the longest increasing subsequence ending at i, C[i] = how many there are of that length.
// A longer one found at j replaces the count; one of equal length adds to it.
long long countLis(const vector<int>& a) {
    int n = a.size();
    vector<int> L(n, 1);
    vector<long long> C(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[i]) continue;
            if (L[j] + 1 > L[i]) L[i] = L[j] + 1, C[i] = C[j];
            else if (L[j] + 1 == L[i]) C[i] += C[j];
        }
    int best = *max_element(L.begin(), L.end());
    long long total = 0;
    for (int i = 0; i < n; i++)
        if (L[i] == best) total += C[i];
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << countLis(a) << "\n";
}
