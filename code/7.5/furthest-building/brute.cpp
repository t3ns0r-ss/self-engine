#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, bricks, ladders;
    cin >> n >> bricks >> ladders;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    int best = 0;
    for (int reach = 1; reach < n; reach++) {  // can we reach the building `reach`? choose which climbs get the ladders
        vector<int> climbs;
        for (int i = 0; i < reach; i++)
            if (h[i + 1] > h[i]) climbs.push_back(h[i + 1] - h[i]);
        int m = climbs.size();
        bool ok = false;
        for (int mask = 0; mask < (1 << m); mask++) {
            if (__builtin_popcount(mask) > ladders) continue;
            long long need = 0;
            for (int i = 0; i < m; i++)
                if (!(mask >> i & 1)) need += climbs[i];
            ok |= need <= bricks;
        }
        if (!ok) break;
        best = reach;
    }
    cout << best << "\n";
}
