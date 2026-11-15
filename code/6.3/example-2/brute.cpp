#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n), b(m);
    for (string& s : a) {
        int x;
        cin >> x;
        s = to_string(x);
    }
    for (string& s : b) {
        int x;
        cin >> x;
        s = to_string(x);
    }
    size_t best = 0;
    for (const string& x : a)
        for (const string& y : b) {
            size_t k = 0;
            while (k < x.size() && k < y.size() && x[k] == y[k]) k++;
            best = max(best, k);
        }
    cout << best << "\n";
}
