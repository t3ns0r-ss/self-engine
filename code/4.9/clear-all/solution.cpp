/*
Problem: clearing symptoms.
Input: k m, then m lines "days cure cause". There are k symptoms (bits 0 to k - 1) and all of them are present at the start.
Taking one medicine takes days (1 <= days <= 10^9) days, removes the symptoms in the bitmask cure, and then adds the symptoms in the
bitmask cause. Medicines can be taken in any order and any number of times.
Output: the fewest days until no symptom is present, or -1 if that never happens.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorems 4.9.2 and 4.9.3. Fewest days to clear all k symptoms. A state is the set of symptoms present, as a bitmask; medicine i
// leads from state s to (s & ~cure[i]) | cause[i] and costs days[i], so Dijkstra runs over the 2^k states.
long long fewestDays(int k, const vector<long long>& days, const vector<int>& cure, const vector<int>& cause) {
    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(1 << k, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;  // (days, state)
    dist[(1 << k) - 1] = 0;
    heap.push({0, (1 << k) - 1});
    while (!heap.empty()) {
        auto [d, state] = heap.top();
        heap.pop();
        if (d > dist[state]) continue;  // an old entry
        if (state == 0) return d;
        for (size_t i = 0; i < days.size(); i++) {
            int next = (state & ~cure[i]) | cause[i];
            if (d + days[i] < dist[next]) dist[next] = d + days[i], heap.push({dist[next], next});
        }
    }
    return -1;
}
// snippet:end

int main() {
    int k, m;
    cin >> k >> m;
    vector<long long> days(m);
    vector<int> cure(m), cause(m);
    for (int i = 0; i < m; i++) cin >> days[i] >> cure[i] >> cause[i];
    cout << fewestDays(k, days, cure, cause) << "\n";
}
