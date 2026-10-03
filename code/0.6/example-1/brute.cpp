// Tries every pair, smallest j first, then smallest i.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < j; i++)
            if (a[i] + a[j] == x) {
                cout << i + 1 << " " << j + 1 << "\n";
                return 0;
            }
    cout << "IMPOSSIBLE\n";
}
