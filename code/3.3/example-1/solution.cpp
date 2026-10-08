/*
Problem: CSES 1158, Book Shop. n books with prices h_i and page counts s_i; buy each book at most once with total
price at most x, maximising the total number of pages.
Input: n x (n <= 1000, x <= 10^5), then the n prices, then the n page counts (each <= 1000).
Output: the largest total number of pages.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (int& p : h) cin >> p;
    for (int& p : s) cin >> p;
    // best[c] = most pages with total price at most c (Theorem 3.3.1); at most 10^6 pages, so int is enough
    vector<int> best(x + 1, 0);
    for (int i = 0; i < n; i++)
        for (int c = x; c >= h[i]; c--) best[c] = max(best[c], best[c - h[i]] + s[i]);
    cout << best[x] << "\n";
}
