/*
Problem: split n numbers into two groups so that the difference of the group sums is as small as possible.
Input: n (1 <= n <= 1000), then n integers (1 <= a_i <= 1000), so the total is at most 10^6.
Output: the smallest possible difference.
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1000000;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int total = 0;
    for (int& x : a) {
        cin >> x;
        total += x;
    }
    // bit s of reach is 1 when some subset of the numbers seen so far sums to s (Theorem 3.3.4)
    bitset<MAXS + 1> reach;
    reach[0] = 1;
    for (int x : a) reach |= reach << x;  // every old sum s also gives s + x; each number used once
    // one group has sum s, the other total - s; the best s is the reachable sum closest to total / 2
    int best = total;
    for (int s = total / 2; s >= 0; s--)
        if (reach[s]) {
            best = total - 2 * s;
            break;
        }
    cout << best << "\n";
}
