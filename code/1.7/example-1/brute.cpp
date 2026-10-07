#include <bits/stdc++.h>
using namespace std;

// tries every assignment of values 0..7 to the scarves (inputs from gen.cpp only)
int main() {
    int n;
    cin >> n;
    vector<int> a(n), x(n, 0);
    for (auto& v : a) cin >> v;
    int total = 1;
    for (int i = 0; i < n; i++) total *= 8;
    for (int code = 0; code < total; code++) {
        int c = code;
        for (int i = 0; i < n; i++) x[i] = c % 8, c /= 8;
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            int s = 0;
            for (int j = 0; j < n; j++)
                if (j != i) s ^= x[j];
            ok = s == a[i];
        }
        if (ok) {
            for (int i = 0; i < n; i++) cout << x[i] << (i + 1 < n ? ' ' : '\n');
            return 0;
        }
    }
}
