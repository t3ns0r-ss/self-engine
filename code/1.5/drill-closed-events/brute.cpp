#include <bits/stdc++.h>
using namespace std;

// Brute force: count the guests on every day of a small range.
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (auto& p : v) cin >> p.first >> p.second;
    int best = 0;
    for (int day = 1; day <= 30; day++) {
        int c = 0;
        for (auto& p : v) if (p.first <= day && day <= p.second) c++;
        best = max(best, c);
    }
    cout << best << "\n";
}
