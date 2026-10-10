#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int& x : arr) cin >> x;
    int best = INT_MAX;
    for (int l = 0; l < n; l++) {
        int v = arr[l];
        for (int r = l; r < n; r++) {
            v &= arr[r];
            best = min(best, abs(v - target));
        }
    }
    cout << best << "\n";
}
