/*
Problem: CSES 1640 Sum of Two Values. Find positions i < j with a_i + a_j = x, or print IMPOSSIBLE.
Any pair is accepted; this program prints the pair with the smallest j, and for it the smallest i.
Input: n x (1 <= n <= 2*10^5, 1 <= x <= 10^9), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: "i j" (1-based) or IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    map<long long, int> firstPos;  // value -> first position where it appeared (Theorem 0.6.3)
    for (int j = 0; j < n; j++) {
        long long a;
        cin >> a;
        auto it = firstPos.find(x - a);  // find, not [], so no empty entries are created
        if (it != firstPos.end()) {
            cout << it->second + 1 << " " << j + 1 << "\n";
            return 0;
        }
        if (!firstPos.count(a)) firstPos[a] = j;
    }
    cout << "IMPOSSIBLE\n";
}
