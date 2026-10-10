#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {3, 5, 1, 4};
    // P1: the sum of a[1..2]. Brute: add the elements. Method: P[3] - P[1].
    vector<int> P = {0};
    for (int x : a) P.push_back(P.back() + x);
    cout << "P1 brute=" << a[1] + a[2] << " method=" << P[3] - P[1] << '\n';
    // N1: a[1] is set to 0, then the sum of a[1..2] is asked, with the prefix sums built before the change.
    vector<int> b = a;
    b[1] = 0;
    cout << "N1 brute=" << b[1] + b[2] << " method=" << P[3] - P[1] << '\n';
    // N2: the maximum of a[1..2], computed as the prefix-sum difference.
    cout << "N2 brute=" << max(a[1], a[2]) << " method=" << P[3] - P[1] << '\n';
}
