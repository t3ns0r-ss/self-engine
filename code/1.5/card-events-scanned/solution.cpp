#include <bits/stdc++.h>
using namespace std;

struct Visit {
    int l, r, w;
};

// The scan of Theorem 1.5.6 on closed integer seconds [l, r], read as [l, r + 1). endShift is 1 for the correct reading
// and 0 for the common mistake of putting the end event at r. Returns {most visits, most weight, seconds in >= 2 visits}.
array<long long, 3> scan(const vector<Visit>& v, int endShift) {
    vector<array<long long, 3>> events;
    for (auto& x : v) events.push_back({x.l, 1, x.w}), events.push_back({x.r + endShift, 0, x.w});
    sort(events.begin(), events.end());
    long long count = 0, weight = 0, mostVisits = 0, mostWeight = 0, atLeast2 = 0;
    for (size_t t = 0; t < events.size(); t++) {
        count += events[t][1] ? 1 : -1, weight += events[t][1] ? events[t][2] : -events[t][2];
        mostVisits = max(mostVisits, count), mostWeight = max(mostWeight, weight);
        if (t + 1 < events.size() && count >= 2) atLeast2 += events[t + 1][0] - events[t][0];
    }
    return {mostVisits, mostWeight, atLeast2};
}

int main() {
    // P1: the seconds covered by at least 2 of the visits [1,4], [2,6], [6,7]. Brute: look at every second.
    vector<Visit> a = {{1, 4, 1}, {2, 6, 1}, {6, 7, 1}};
    long long brute = 0;
    for (int x = 0; x <= 8; x++) {
        int c = 0;
        for (auto& v : a) c += v.l <= x && x <= v.r;
        brute += c >= 2;
    }
    cout << "P1 brute=" << brute << " method=" << scan(a, 1)[2] << '\n';
    // P2: the largest total weight at one second for [1,3] weight 5, [3,5] weight 2, [4,6] weight 10.
    vector<Visit> b = {{1, 3, 5}, {3, 5, 2}, {4, 6, 10}};
    brute = 0;
    for (int x = 0; x <= 7; x++) {
        long long wsum = 0;
        for (auto& v : b)
            if (v.l <= x && x <= v.r) wsum += v.w;
        brute = max(brute, wsum);
    }
    cout << "P2 brute=" << brute << " method=" << scan(b, 1)[1] << '\n';
    // N1: [1,3] and [3,5] share the second 3; the end event is put at r instead of r + 1.
    vector<Visit> c = {{1, 3, 1}, {3, 5, 1}};
    brute = 0;
    for (int x = 0; x <= 6; x++) {
        int cnt = 0;
        for (auto& v : c) cnt += v.l <= x && x <= v.r;
        brute = max<long long>(brute, cnt);
    }
    cout << "N1 brute=" << brute << " method=" << scan(c, 0)[0] << '\n';
    // N2: the most pairwise disjoint intervals among [1,5), [2,3), [4,6), [7,8), answered with the largest overlap.
    vector<pair<int, int>> d = {{1, 5}, {2, 3}, {4, 6}, {7, 8}};
    int best = 0;
    for (int mask = 0; mask < 16; mask++) {
        bool ok = true;
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if ((mask >> i & 1) && (mask >> j & 1) && max(d[i].first, d[j].first) < min(d[i].second, d[j].second)) ok = false;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    vector<Visit> e;
    for (auto [l, r] : d) e.push_back({l, r - 1, 1});  // [l, r) as closed seconds l .. r - 1
    cout << "N2 brute=" << best << " method=" << scan(e, 1)[0] << '\n';
}
