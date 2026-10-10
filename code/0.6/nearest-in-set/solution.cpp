/*
Problem: a multiset of integers under q queries: "1 x" adds x, "2 x" removes one copy of x (present),
"3 x" prints the largest element <= x, "4 x" the smallest element >= x (or -1 if none).
Input: q (q <= 2*10^5), then the queries (0 <= x <= 10^9).
Output: one line per query of type 3 or 4.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.4. "1 x" adds x, "2 x" removes one copy of x, "3 x" asks for the largest element <= x,
// "4 x" for the smallest element >= x (-1 if none).
vector<int> processMultiset(const vector<array<int, 2>>& queries) {
    multiset<int> s;
    vector<int> answers;
    for (auto [type, x] : queries) {
        if (type == 1) {
            s.insert(x);
        } else if (type == 2) {
            s.erase(s.find(x));  // one copy; s.erase(x) would remove every copy
        } else if (type == 3) {
            auto it = s.upper_bound(x);  // first element > x
            answers.push_back(it == s.begin() ? -1 : *prev(it));  // the one before it is the largest <= x
        } else {
            auto it = s.lower_bound(x);  // first element >= x
            answers.push_back(it == s.end() ? -1 : *it);
        }
    }
    return answers;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    vector<array<int, 2>> queries(q);
    for (auto& e : queries) cin >> e[0] >> e[1];
    for (int a : processMultiset(queries)) cout << a << "\n";
}
