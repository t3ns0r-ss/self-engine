#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    cin >> N;
    long long ans = 0;
    for (long long x = 1; x <= N; x++) {
        int d = 0;
        for (long long k = 1; k * k <= x; k++)
            if (x % k == 0) d += (k * k == x) ? 1 : 2;
        if (d == 9) ans++;
    }
    cout << ans << "\n";
}
