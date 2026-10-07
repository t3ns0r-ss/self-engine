// Lists all sums, sorts them, and takes the k-th.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<long long> A(n), B(m), s;
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;
    for (long long a : A)
        for (long long b : B) s.push_back(a + b);
    sort(s.begin(), s.end());
    cout << s[k - 1] << "\n";
}
