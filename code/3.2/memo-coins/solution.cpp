/*
Problem: a coin worth n can be exchanged for three coins worth floor(n/2), floor(n/3) and floor(n/4), and each of
those can be exchanged again; any coin can instead be sold for its value. Print the most money obtainable from n.
Input: one integer n (0 <= n <= 10^12).
Output: g(n), where g(n) = max(n, g(n/2) + g(n/3) + g(n/4)) with integer division.
*/
#include <bits/stdc++.h>
using namespace std;

map<long long, long long> cache;  // value of each argument already computed (Theorem 3.2.4)

long long g(long long n) {
    if (n == 0) return 0;  // base case
    auto it = cache.find(n);
    if (it != cache.end()) return it->second;  // computed before: return at once
    long long res = max(n, g(n / 2) + g(n / 3) + g(n / 4));
    cache[n] = res;
    return res;
}

int main() {
    long long n;
    cin >> n;
    cout << g(n) << "\n";
}
