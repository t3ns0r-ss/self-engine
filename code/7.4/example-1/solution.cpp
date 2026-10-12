#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 630, Course Schedule III. n courses (up to 10^4); course i takes duration_i days and must be finished by day lastDay_i.
One course at a time, no breaks. Print the largest number of courses that can be taken.
Input: n, then n lines "duration lastDay".
*/


// snippet:begin
// Theorem 7.4.1: courses in the order of the last days; take each; when the total time passes the last day of the course just
// added, drop the longest course taken so far (it may be the one just added).
int scheduleCourses(vector<pair<int, int>> courses) {
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

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> courses(n);
    for (auto& [d, l] : courses) cin >> d >> l;
    cout << scheduleCourses(courses) << "\n";
}
