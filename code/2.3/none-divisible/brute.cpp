#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    int m;
    cin >> N >> m;
    vector<long long> a(m);
    for (auto& x : a) cin >> x;
    long long count = 0;
    for (long long x = 1; x <= N; x++) {
        bool ok = true;
        for (long long v : a)
            if (x % v == 0) ok = false;
        if (ok) count++;
    }
    cout << count << "\n";
}
