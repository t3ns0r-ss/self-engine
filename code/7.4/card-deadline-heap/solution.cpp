#include <bits/stdc++.h>
using namespace std;

struct Course { int duration, lastDay, value; };
// method: sort by the last day, take every course, and drop the longest taken when the total passes the last day; the result is the
// total value of the courses left (with all values 1, the number of courses).
long long method(vector<Course> c) {
    sort(c.begin(), c.end(), [](auto& a, auto& b) { return a.lastDay < b.lastDay; });
    priority_queue<pair<int, int>> taken;  // (duration, value)
    long long total = 0;
    for (auto& x : c) {
        taken.push({x.duration, x.value}), total += x.duration;
        if (total > x.lastDay) total -= taken.top().first, taken.pop();
    }
    long long value = 0;
    while (!taken.empty()) value += taken.top().second, taken.pop();
    return value;
}
// brute: every subset in the order of the last days; the largest total value.
long long brute(vector<Course> c) {
    sort(c.begin(), c.end(), [](auto& a, auto& b) { return a.lastDay < b.lastDay; });
    int n = c.size();
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long time = 0, value = 0;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) time += c[i].duration, value += c[i].value, ok &= time <= c[i].lastDay;
        if (ok) best = max(best, value);
    }
    return best;
}
// The balance form: potions in a row; the health must stay non-negative; the largest number drunk.
int potionsMethod(const vector<long long>& a) {
    priority_queue<long long, vector<long long>, greater<long long>> drunk;
    long long health = 0;
    for (long long x : a) {
        drunk.push(x), health += x;
        if (health < 0) health -= drunk.top(), drunk.pop();
    }
    return drunk.size();
}
int potionsBrute(const vector<long long>& a) {
    int n = a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long health = 0;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) health += a[i], ok &= health >= 0;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    return best;
}
int main() {
    vector<Course> c1 = {{100, 200, 1}, {200, 1300, 1}, {1000, 1250, 1}, {2000, 3200, 1}};
    vector<long long> p = {4, -4, 1, -3, 1, -3};
    vector<Course> c3 = {{3, 4, 7}, {2, 4, 6}};  // now the values differ
    cout << "P1 brute=" << brute(c1) << " method=" << method(c1) << "\n";
    cout << "P2 brute=" << potionsBrute(p) << " method=" << potionsMethod(p) << "\n";
    cout << "N1 brute=" << brute(c3) << " method=" << method(c3) << "\n";
}
