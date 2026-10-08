#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    bool pairwise = true;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (gcd(a[i], a[j]) != 1) pairwise = false;
    int g = 0;
    for (int v : a) g = gcd(g, v);
    if (pairwise) cout << "pairwise coprime\n";
    else if (g == 1) cout << "setwise coprime\n";
    else cout << "not coprime\n";
}
