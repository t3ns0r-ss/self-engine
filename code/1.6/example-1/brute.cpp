#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = i + 1; j < n; j++) {
            bool ok = true;
            for (int k = i + 1; k < j; k++)
                if (h[k] > h[j]) ok = false;
            cnt += ok;
        }
        cout << cnt << (i + 1 < n ? ' ' : '\n');
    }
}
