// Takes all T steps one by one (the generator keeps T small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, x;
    long long t;
    cin >> k >> x >> t;
    vector<int> nxt(k);
    for (auto& v : nxt) cin >> v;
    for (long long i = 0; i < t; i++) x = nxt[x];
    cout << x << "\n";
}
