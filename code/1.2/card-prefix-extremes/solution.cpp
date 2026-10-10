#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the best a_j - a_i with i < j in 7 1 5 3 6 4. Brute: all pairs. Method: the running minimum.
    vector<int> a = {7, 1, 5, 3, 6, 4};
    int brute = INT_MIN, method = INT_MIN, mn = a[0];
    for (int i = 0; i < 6; i++) for (int j = i + 1; j < 6; j++) brute = max(brute, a[j] - a[i]);
    for (int j = 1; j < 6; j++) { method = max(method, a[j] - mn); mn = min(mn, a[j]); }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the maximum of a[2..3] in 3 5 1 4, answered with the prefix maximum up to index 3.
    vector<int> b = {3, 5, 1, 4};
    cout << "N1 brute=" << max(b[2], b[3]) << " method=" << *max_element(b.begin(), b.begin() + 4) << '\n';
    // N2: the best non-empty subarray sum of -3 -1, with the running minimum updated before it is used.
    vector<int> c = {-3, -1};
    int P = 0, minP = 0, best = INT_MIN;
    for (int x : c) { P += x; minP = min(minP, P); best = max(best, P - minP); }
    cout << "N2 brute=" << -1 << " method=" << best << '\n';
}
