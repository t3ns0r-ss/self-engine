/*
Problem: CSES 1158, Book Shop. n books with prices h_i and page counts s_i; buy each book at most once with total
price at most x, maximising the total number of pages.
Input: n x (n <= 1000, x <= 10^5), then the n prices, then the n page counts (each <= 1000).
Output: the largest total number of pages.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// CSES 1158. best[c] = the most pages with total price at most c; each book is used at most once.
int bookShop(const vector<int>& h, const vector<int>& s, int x) {
    vector<int> best(x + 1, 0);  // at most 10^6 pages, so int is enough
    for (size_t i = 0; i < h.size(); i++)
        for (int c = x; c >= h[i]; c--) best[c] = max(best[c], best[c - h[i]] + s[i]);
    return best[x];
}
// snippet:end

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (int& p : h) cin >> p;
    for (int& p : s) cin >> p;
    cout << bookShop(h, s, x) << "\n";
}
