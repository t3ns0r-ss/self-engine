#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> l;
long long cnt = 0;

void rec(int i, int left) {  // try every value of x_i in turn
    if (i == k - 1) {
        if (left >= l[i]) cnt++;
        return;
    }
    for (int x = l[i]; x <= left; x++) rec(i + 1, left - x);
}

int main() {
    cin >> n >> k;
    l.resize(k);
    for (auto& x : l) cin >> x;
    rec(0, n);
    cout << cnt % 998244353 << "\n";
}
