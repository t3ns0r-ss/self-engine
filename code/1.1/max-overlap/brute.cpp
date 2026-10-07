// Walks every integer point up to the largest r and counts the intervals containing it.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    int maxR = 0;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        maxR = max(maxR, r[i]);
    }
    int best = 0;
    long long covered = 0;
    for (int x = 0; x <= maxR; x++) {
        int c = 0;
        for (int i = 0; i < n; i++) c += l[i] <= x && x <= r[i];
        best = max(best, c);
        covered += c > 0;
    }
    cout << best << " " << covered << "\n";
}
