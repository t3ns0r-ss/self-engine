#include <bits/stdc++.h>
using namespace std;

// Reference: test every pair of a horizontal and a vertical segment.
int main() {
    int n;
    cin >> n;
    vector<array<int, 4>> segs(n);
    for (auto& s : segs) cin >> s[0] >> s[1] >> s[2] >> s[3];
    long long total = 0;
    for (auto& h : segs)
        for (auto& v : segs)
            if (h[1] == h[3] && v[0] == v[2] && h[0] <= v[0] && v[0] <= h[2] && v[1] <= h[1] && h[1] <= v[3]) total++;
    cout << total << "\n";
}
