#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 871, Minimum Number of Refueling Stops. A car starts with startFuel units of fuel and drives to a target at distance
`target`; one unit of fuel is used for one unit of distance. Station i is at distance position_i and has fuel_i units (all taken at a
stop). Print the fewest stops needed to reach the target, or -1. (Up to 500 stations in the original; here any number.)
Input: target, startFuel and n, then n lines "position fuel".
*/


// snippet:begin
// Theorem 7.4.2: drive as far as the fuel reaches; the stations passed go into a heap of fuels. When the target is not reached, take the
// largest fuel in the heap (as if the car had stopped there), until the target is reached or the heap is empty.
int minRefuelStops(int target, int startFuel, vector<pair<int, int>> stations) {
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

int main() {
    int target, startFuel, n;
    cin >> target >> startFuel >> n;
    vector<pair<int, int>> stations(n);
    for (auto& [p, f] : stations) cin >> p >> f;
    cout << minRefuelStops(target, startFuel, stations) << "\n";
}
