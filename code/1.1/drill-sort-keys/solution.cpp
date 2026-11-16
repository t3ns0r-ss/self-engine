/*
Drill (about 4 minutes). n contestants, each with a score, a penalty and an id. Rank them: higher score first; on equal
scores the smaller penalty first; on equal penalties the smaller id first. Print the ids in rank order.
Input: n, then n lines "id score penalty" (ids are different, 1 <= id <= 10^9, 0 <= score, penalty <= 10^9), n <= 2*10^5.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Compare tuples: put the keys in priority order and flip the sign of the one that must go descending.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<long long, 3>> v(n);  // {-score, penalty, id}: the smallest tuple ranks first
    for (auto& c : v) {
        long long id, score, penalty;
        cin >> id >> score >> penalty;
        c = {-score, penalty, id};
    }
    sort(v.begin(), v.end());
    for (auto& c : v) cout << c[2] << "\n";
}
// snippet:end
