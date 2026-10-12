#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.4.1. Courses (duration, last day) in the order of the last days. Take every course; when the total time passes the last
// day of the course just added, drop the longest course taken so far. The heap holds the durations of the courses taken.
int mostCourses(vector<pair<int, int>> courses) {
    sort(courses.begin(), courses.end(), [](auto& a, auto& b) { return a.second < b.second; });
    priority_queue<int> taken;
    long long total = 0;
    for (auto [duration, lastDay] : courses) {
        taken.push(duration), total += duration;
        if (total > lastDay) total -= taken.top(), taken.pop();
    }
    return taken.size();
}
// snippet:end

int bruteCourses(const vector<pair<int, int>>& courses) {  // every subset, taken in the order of the last days
    int n = courses.size(), best = 0;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return courses[a].second < courses[b].second; });
    for (int mask = 0; mask < (1 << n); mask++) {
        long long time = 0;
        bool ok = true;
        for (int i : order)
            if (mask >> i & 1) {
                time += courses[i].first;
                ok &= time <= courses[i].second;
            }
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    return best;
}

int main() {
    cout << "courses 1: " << mostCourses({{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}) << "\n";
    cout << "courses 2: " << mostCourses({{3, 3}, {2, 4}, {2, 5}}) << "\n";
    // Check (not printed): 3000 random sets of up to 8 courses, against all subsets.
    mt19937 rng(21);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 8 + 1;
        vector<pair<int, int>> c(n);
        for (auto& [d, l] : c) d = rng() % 6 + 1, l = rng() % 14 + 1;
        if (mostCourses(c) != bruteCourses(c)) return 1;
    }
}
