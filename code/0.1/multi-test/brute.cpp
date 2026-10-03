// For each x, adds up (x - a_j) over all j: positive exactly when x is above the average.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int test = 0; test < t; test++) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto& x : a) cin >> x;
        int count = 0;
        for (int i = 0; i < n; i++) {
            long long diff = 0;
            for (int j = 0; j < n; j++) diff += a[i] - a[j];
            if (diff > 0) count++;
        }
        cout << count << "\n";
    }
}
