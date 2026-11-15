#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> c, a;
long long cnt = 0;

void rec(int i) {
    if (i == n) {
        cnt++;
        return;
    }
    for (int v = 1; v <= c[i]; v++) {
        bool used = false;
        for (int j = 0; j < i; j++) used |= (a[j] == v);
        if (!used) a[i] = v, rec(i + 1);
    }
}

int main() {
    cin >> n;
    c.resize(n), a.resize(n);
    for (auto& x : c) cin >> x;
    rec(0);
    cout << cnt % 1000000007 << "\n";
}
