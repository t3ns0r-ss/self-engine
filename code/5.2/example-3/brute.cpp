#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int& v : x) cin >> v;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        cout << x[p - 1] << (i + 1 < n ? ' ' : '\n');
        x.erase(x.begin() + p - 1);
    }
}
