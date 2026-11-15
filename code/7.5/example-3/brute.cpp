#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> c(n);
    for (auto& [a, b] : c) cin >> a >> b;
    int best = 0;  // the most customers present on one day
    for (int day = 1; day <= 30; day++) {
        int present = 0;
        for (auto& [a, b] : c) present += a <= day && day <= b;
        best = max(best, present);
    }
    cout << best << "\n";
}
