#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long s, x;
        cin >> s >> x;
        long long found = -1;
        for (long long a = 0; a <= s && found < 0; a++)
            if ((a ^ (s - a)) == x) found = a;
        if (found < 0) cout << -1 << "\n";
        else cout << found << " " << s - found << "\n";
    }
}
