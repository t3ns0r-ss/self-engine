// Three nested loops over x, y, z.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k, s, count = 0;
    cin >> k >> s;
    for (long long x = 0; x <= k; x++)
        for (long long y = 0; y <= k; y++)
            for (long long z = 0; z <= k; z++)
                if (x + 2 * y + 3 * z == s) count++;
    cout << count << "\n";
}
