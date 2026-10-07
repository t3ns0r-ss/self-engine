// Walks every day up to the last login day and counts the players logged in on it.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    long long last = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        last = max(last, a[i] + b[i] - 1);
    }
    vector<long long> days(n + 1, 0);
    for (long long d = 1; d <= last; d++) {
        int c = 0;
        for (int i = 0; i < n; i++) c += a[i] <= d && d <= a[i] + b[i] - 1;
        days[c]++;
    }
    for (int k = 1; k <= n; k++) cout << days[k] << (k < n ? ' ' : '\n');
}
