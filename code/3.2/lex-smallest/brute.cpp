// Brute force: every bitmask with no two adjacent bits; keep the best sum, then the smallest position list.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long best = -1;
    vector<int> bestList;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask & (mask >> 1)) continue;
        long long s = 0;
        vector<int> list;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) {
                s += a[i];
                list.push_back(i + 1);
            }
        if (s > best || (s == best && list < bestList)) {
            best = s;
            bestList = list;
        }
    }
    cout << best << "\n" << bestList.size() << "\n";
    for (int j = 0; j < (int)bestList.size(); j++) cout << bestList[j] << (j + 1 < (int)bestList.size() ? ' ' : '\n');
}
