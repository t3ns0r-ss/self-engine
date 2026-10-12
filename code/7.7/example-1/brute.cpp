#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    do {
        set<int> differences;
        for (int i = 0; i + 1 < n; i++) differences.insert(abs(p[i] - p[i + 1]));
        if ((int)differences.size() == k) {
            cout << "OK\n";
            return 0;
        }
    } while (next_permutation(p.begin(), p.end()));
    cout << "NONE\n";
}
