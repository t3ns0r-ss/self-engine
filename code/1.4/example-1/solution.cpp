/*
Problem: ABC 143 D Triangles. Count the ways to choose 3 of N sticks (as a set of sticks) whose
lengths a, b, c satisfy a < b + c, b < c + a and c < a + b.
Input: N (3 <= N <= 2000), then L_1 .. L_N (1 <= L_i <= 1000).
Output: the number of triangles.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> L(n);
    for (auto& x : L) cin >> x;
    sort(L.begin(), L.end());  // the answer counts sets of sticks, so the order does not matter
    long long count = 0;       // up to C(2000, 3), about 1.3*10^9
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            // with L[i] <= L[j] <= L[k], only L[k] < L[i] + L[j] can fail;
            // the valid k > j are those before the first index with L[k] >= L[i] + L[j]
            int end = lower_bound(L.begin() + j + 1, L.end(), L[i] + L[j]) - L.begin();
            count += end - (j + 1);
        }
    cout << count << "\n";
}
