#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long M;
    cin >> n >> M;
    vector<int> ea(n - 1), eb(n - 1);
    for (int i = 0; i + 1 < n; i++) cin >> ea[i] >> eb[i], ea[i]--, eb[i]--;
    long long count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i + 1 < n; i++) ok = ok && !((mask >> ea[i] & 1) && (mask >> eb[i] & 1));
        count += ok;
    }
    cout << count % M << "\n";
}
