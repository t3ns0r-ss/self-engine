#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long x, m;
        cin >> x >> m;
        for (long long s = x; s < x + m; s++) total ^= s;
    }
    cout << (total != 0 ? "tolik" : "bolik") << "\n";
}
