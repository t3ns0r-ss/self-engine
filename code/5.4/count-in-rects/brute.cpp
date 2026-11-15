#include <bits/stdc++.h>
using namespace std;

// Reference: for every rectangle, test every point.
int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> points(n);
    for (auto& p : points) cin >> p.first >> p.second;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int count = 0;
        for (auto& [x, y] : points) count += (a <= x && x <= b && c <= y && y <= d);
        cout << count << "\n";
    }
}
