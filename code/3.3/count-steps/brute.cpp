// Brute force: list every sequence of steps by recursion and count those that end exactly at n.
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> s;
long long total = 0;

void go(int at) {
    if (at == n) {
        total++;
        return;
    }
    for (int step : s)
        if (at + step <= n) go(at + step);
}

int main() {
    cin >> n >> m;
    s.resize(m);
    for (int& x : s) cin >> x;
    go(0);
    cout << total % 1000000007 << "\n";
}
