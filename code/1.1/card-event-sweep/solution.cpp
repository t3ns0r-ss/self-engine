#include <bits/stdc++.h>
using namespace std;

int sweep(vector<pair<int, int>> events) {
    sort(events.begin(), events.end());
    int cur = 0, best = 0;
    for (auto [t, c] : events) cur += c, best = max(best, cur);
    return best;
}

int main() {
    // P1: [1, 4), [2, 5), [4, 6): the most intervals at one point. Brute: test every point. Method: the sweep.
    vector<pair<int, int>> iv = {{1, 4}, {2, 5}, {4, 6}}, ev;
    int brute = 0;
    for (int t = 0; t < 10; t++) { int c = 0; for (auto [s, e] : iv) c += s <= t && t < e; brute = max(brute, c); }
    for (auto [s, e] : iv) ev.push_back({s, +1}), ev.push_back({e, -1});
    cout << "P1 brute=" << brute << " method=" << sweep(ev) << '\n';
    // P2: [1, 3), [3, 5): the half-open intervals touch but do not overlap.
    iv = {{1, 3}, {3, 5}};
    ev.clear();
    brute = 0;
    for (int t = 0; t < 10; t++) { int c = 0; for (auto [s, e] : iv) c += s <= t && t < e; brute = max(brute, c); }
    for (auto [s, e] : iv) ev.push_back({s, +1}), ev.push_back({e, -1});
    cout << "P2 brute=" << brute << " method=" << sweep(ev) << '\n';
    // N1: the same intervals with starts sorted BEFORE ends at equal times (the event (3, -1) is written as (3, +2)).
    vector<pair<int, int>> wrong = {{1, +1}, {3, -1}, {3, +1}, {5, -1}};
    for (auto& e : wrong) e.second = -e.second;  // flip the sign order: at time 3 the start now sorts first
    int cur = 0, best = 0;
    sort(wrong.begin(), wrong.end());
    for (auto [t, c] : wrong) { cur -= c; best = max(best, cur); }
    cout << "N1 brute=" << brute << " method=" << best << '\n';
    // N2: the closed integer intervals [1, 3] and [3, 5] share the point 3, but are read as half-open [1, 3), [3, 5).
    int closed = 0;
    for (int t = 0; t < 10; t++) { int c = (1 <= t && t <= 3) + (3 <= t && t <= 5); closed = max(closed, c); }
    cout << "N2 brute=" << closed << " method=" << sweep({{1, +1}, {3, -1}, {3, +1}, {5, -1}}) << '\n';
}
