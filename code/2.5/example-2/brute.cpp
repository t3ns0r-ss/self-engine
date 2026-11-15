#include <bits/stdc++.h>
using namespace std;

long long cnt;

void fill(int left, int k) {  // choose each entry as a divisor of what remains
    if (left == 0) {
        if (k == 1) cnt++;
        return;
    }
    for (int d = 1; d <= k; d++)
        if (k % d == 0) fill(left - 1, k / d);
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;
        cnt = 0;
        fill(n, k);
        cout << cnt % 1000000007 << "\n";
    }
}
