#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    long long coprime = 0;
    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int g = gcd(a[i], a[j]);
            if (g == 1) coprime++;
            best = max(best, g);
        }
    cout << coprime << " " << best << "\n";
}
