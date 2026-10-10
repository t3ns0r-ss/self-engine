/*
Problem: process q queries on a collection of integers: "1 x" adds x, "2 x" asks whether x is present
(YES/NO), "3" asks how many distinct values it holds.
Input: q (q <= 2*10^5), then the queries (0 <= x <= 10^9).
Output: one line per query of type 2 or 3.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.2. "1 x" adds x, "2 x" asks whether x is present, "3" asks for the number of distinct values.
vector<string> processQueries(const vector<array<int, 2>>& queries) {
    set<int> s;  // each distinct value once
    vector<string> answers;
    for (auto [type, x] : queries) {
        if (type == 1) s.insert(x);  // no effect if x is already there
        else if (type == 2) answers.push_back(s.count(x) ? "YES" : "NO");
        else answers.push_back(to_string(s.size()));
    }
    return answers;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    vector<array<int, 2>> queries(q, {0, 0});
    for (auto& e : queries) {
        cin >> e[0];
        if (e[0] != 3) cin >> e[1];
    }
    for (const string& a : processQueries(queries)) cout << a << "\n";
}
