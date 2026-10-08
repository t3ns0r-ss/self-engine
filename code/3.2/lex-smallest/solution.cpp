/*
Problem: choose elements of an array of positive integers, no two adjacent, with the largest sum; among all
choices with that sum, print the one whose list of positions is lexicographically smallest.
Input: n (1 <= n <= 10^5), then a_1..a_n (1 <= a_i <= 10^9).
Output: the largest sum, then the number of chosen positions, then the positions (1-based) in increasing order.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // suffix table: best[i] = the largest sum using only positions i..n-1 (filled from the end)
    vector<long long> best(n + 2, 0);
    for (int i = n - 1; i >= 0; i--) best[i] = max(best[i + 1], a[i] + best[i + 2]);
    // walk forward (Theorem 3.2.6): take position i whenever taking it still reaches the optimum,
    // which makes the first chosen position as small as possible, then the second, and so on
    vector<int> chosen;
    int i = 0;
    while (i < n) {
        if (a[i] + best[i + 2] == best[i]) {
            chosen.push_back(i + 1);
            i += 2;
        } else {
            i += 1;
        }
    }
    cout << best[0] << "\n" << chosen.size() << "\n";
    for (int j = 0; j < (int)chosen.size(); j++) cout << chosen[j] << (j + 1 < (int)chosen.size() ? ' ' : '\n');
}
