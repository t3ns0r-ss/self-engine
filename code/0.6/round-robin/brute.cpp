// Walks around the task numbers cyclically, giving Q units to every unfinished task in turn.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long Q;
    cin >> n >> Q;
    vector<long long> t(n);
    for (auto& x : t) cin >> x;
    vector<int> order;
    int i = 0;
    while ((int)order.size() < n) {
        if (t[i] > 0) {
            if (t[i] <= Q) {
                order.push_back(i + 1);
                t[i] = 0;
            } else {
                t[i] -= Q;
            }
        }
        i = (i + 1) % n;
    }
    for (int k = 0; k < n; k++) cout << order[k] << (k + 1 < n ? ' ' : '\n');
}
