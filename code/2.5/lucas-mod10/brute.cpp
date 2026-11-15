#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (a.size() > 1) {
        vector<int> b(a.size() - 1);
        for (size_t i = 0; i + 1 < a.size(); i++) b[i] = (a[i] + a[i + 1]) % 10;
        a = b;
    }
    cout << a[0] << "\n";
}
