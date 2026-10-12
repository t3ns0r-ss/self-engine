#include <bits/stdc++.h>
using namespace std;

struct Event { int first, last, value; };
// method: sweep the days; the heap holds the open events by their last day (and their values); each day attend the one that ends first.
// Returns the total value attended (with all values 1, the number of events).
long long method(vector<Event> e) {
    sort(e.begin(), e.end(), [](auto& a, auto& b) { return a.first < b.first; });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> open;  // (last day, value)
    long long total = 0;
    size_t next = 0;
    for (int day = 1; next < e.size() || !open.empty(); day++) {
        if (open.empty()) day = max(day, e[next].first);
        while (next < e.size() && e[next].first <= day) open.push({e[next].last, e[next].value}), next++;
        while (!open.empty() && open.top().first < day) open.pop();
        if (!open.empty()) total += open.top().second, open.pop();
    }
    return total;
}
// brute: every subset of the events that can be given distinct days (checked by trying all assignments of the days); the largest value.
long long brute(const vector<Event>& e) {
    int n = e.size();
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> chosen;
        long long value = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) chosen.push_back(i), value += e[i].value;
        vector<int> days(chosen.size());
        // try all assignments of days to the chosen events (distinct days, within the windows)
        function<bool(size_t, int)> go = [&](size_t k, int used) {
            if (k == chosen.size()) return true;
            for (int d = e[chosen[k]].first; d <= e[chosen[k]].last; d++)
                if (!(used >> d & 1) && go(k + 1, used | 1 << d)) return true;
            return false;
        };
        if (go(0, 0)) best = max(best, value);
    }
    return best;
}
// The team: sort by efficiency and keep the k largest speeds in a heap.
long long teamMethod(const vector<int>& speed, const vector<int>& eff, int k) {
    vector<int> order(speed.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return eff[a] > eff[b]; });
    priority_queue<int, vector<int>, greater<int>> team;
    long long sum = 0, best = 0;
    for (int i : order) {
        team.push(speed[i]), sum += speed[i];
        if ((int)team.size() > k) sum -= team.top(), team.pop();
        best = max(best, sum * eff[i]);
    }
    return best;
}
long long teamBrute(const vector<int>& speed, const vector<int>& eff, int k) {
    int n = speed.size();
    long long best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) > k) continue;
        long long sum = 0, low = INT_MAX;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) sum += speed[i], low = min<long long>(low, eff[i]);
        best = max(best, sum * low);
    }
    return best;
}
int main() {
    vector<Event> e1 = {{1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {1, 2, 1}};
    vector<Event> e3 = {{1, 1, 1}, {1, 1, 5}};  // now the events have values
    cout << "P1 brute=" << brute(e1) << " method=" << method(e1) << "\n";
    cout << "P2 brute=" << teamBrute({2, 10, 3, 1, 5, 8}, {5, 4, 3, 9, 7, 2}, 2) << " method=" << teamMethod({2, 10, 3, 1, 5, 8}, {5, 4, 3, 9, 7, 2}, 2) << "\n";
    cout << "N1 brute=" << brute(e3) << " method=" << method(e3) << "\n";
}
