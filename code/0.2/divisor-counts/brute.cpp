// Counts the divisors of each k by trying every d from 1 to k.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long total = 0;
    int best = 0;
    for (int k = 1; k <= n; k++) {
        int c = 0;
        for (int d = 1; d <= k; d++)
            if (k % d == 0) c++;
        total += c;
        best = max(best, c);
    }
    cout << total << " " << best << "\n";
}
