#include <bits/stdc++.h>
using namespace std;

struct Station { int position, fuel, cost; };
// method: reach as far as the fuel goes; when stuck, use the passed station with the largest fuel. Returns the total cost of the stops
// used (the number of stops when all costs are 1), or -1.
long long method(int target, int startFuel, vector<Station> s) {
    sort(s.begin(), s.end(), [](auto& a, auto& b) { return a.position < b.position; });
    priority_queue<pair<int, int>> passed;  // (fuel, cost)
    long long reach = startFuel, cost = 0;
    size_t next = 0;
    while (reach < target) {
        while (next < s.size() && s[next].position <= reach) passed.push({s[next].fuel, s[next].cost}), next++;
        if (passed.empty()) return -1;
        reach += passed.top().first, cost += passed.top().second, passed.pop();
    }
    return cost;
}
// brute: every subset used in the order of the positions; the least total cost.
long long brute(int target, int startFuel, vector<Station> s) {
    sort(s.begin(), s.end(), [](auto& a, auto& b) { return a.position < b.position; });
    int n = s.size();
    long long best = -1;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long reach = startFuel, cost = 0;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) ok &= s[i].position <= reach, reach += s[i].fuel, cost += s[i].cost;
        if (ok && reach >= target && (best < 0 || cost < best)) best = cost;
    }
    return best;
}
// The furthest building: bricks and ladders; method with the heap of paid climbs, brute over the choices of the ladders.
int buildingMethod(const vector<int>& h, int bricks, int ladders) {
    priority_queue<int> paid;
    for (size_t i = 0; i + 1 < h.size(); i++) {
        int climb = h[i + 1] - h[i];
        if (climb <= 0) continue;
        paid.push(climb), bricks -= climb;
        if (bricks < 0) {
            if (ladders == 0) return i;
            ladders--, bricks += paid.top(), paid.pop();
        }
    }
    return h.size() - 1;
}
int buildingBrute(const vector<int>& h, int bricks, int ladders) {
    int n = h.size(), best = 0;
    for (int reach = 1; reach < n; reach++) {
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
    return best;
}
int main() {
    vector<Station> s1 = {{10, 60, 1}, {20, 30, 1}, {30, 30, 1}, {60, 40, 1}};
    vector<int> h = {4, 2, 7, 6, 9, 14, 12};
    vector<Station> s3 = {{1, 10, 100}, {1, 6, 1}, {1, 5, 1}};  // now the stations have different prices
    cout << "P1 brute=" << brute(100, 10, s1) << " method=" << method(100, 10, s1) << "\n";
    cout << "P2 brute=" << buildingBrute(h, 5, 1) << " method=" << buildingMethod(h, 5, 1) << "\n";
    cout << "N1 brute=" << brute(10, 1, s3) << " method=" << method(10, 1, s3) << "\n";
}
