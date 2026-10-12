#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.4.2. Stations (position, fuel); the tank holds startFuel at the start and the target is at `target`. Drive as far as the fuel
// reaches; the stations passed go into a heap of fuels, and when the target is not reached, the largest fuel in the heap is taken,
// as if the car had stopped at that station on the way. Returns the fewest stops, or -1.
int fewestStops(int target, int startFuel, vector<pair<int, int>> stations) {
    sort(stations.begin(), stations.end());
    priority_queue<int> passed;
    long long reach = startFuel;
    int stops = 0;
    size_t next = 0;
    while (reach < target) {
        while (next < stations.size() && stations[next].first <= reach) passed.push(stations[next++].second);
        if (passed.empty()) return -1;
        reach += passed.top(), passed.pop(), stops++;
    }
    return stops;
}
// snippet:end

int bruteStops(int target, int startFuel, vector<pair<int, int>> stations) {  // every subset, used in the order of the positions
    sort(stations.begin(), stations.end());
    int n = stations.size(), best = -1;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long reach = startFuel;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                ok &= stations[i].first <= reach;
                reach += stations[i].second;
            }
        if (ok && reach >= target && (best < 0 || __builtin_popcount(mask) < best)) best = __builtin_popcount(mask);
    }
    return best;
}

int main() {
    cout << "stops 1: " << fewestStops(100, 10, {{10, 60}, {20, 30}, {30, 30}, {60, 40}}) << "\n";
    cout << "stops 2: " << fewestStops(100, 1, {{10, 100}}) << "\n";
    cout << "stops 3: " << fewestStops(1, 1, {}) << "\n";
    // Check (not printed): 3000 random cases of up to 8 stations, against all subsets.
    mt19937 rng(22);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 8, target = rng() % 30 + 1, start = rng() % 6 + 1;
        vector<pair<int, int>> s(n);
        for (auto& [p, f] : s) p = rng() % 20 + 1, f = rng() % 9 + 1;
        if (fewestStops(target, start, s) != bruteStops(target, start, s)) return 1;
    }
}
