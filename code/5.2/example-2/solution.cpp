#include <bits/stdc++.h>
using namespace std;

/*
Problem (CSES 1734, Distinct Values Queries): n numbers (up to 10^9) and q questions "how many different values among positions l..r" (1-based).
Input: n q, the n numbers, then q lines l r.
Output: the answer to each question on its own line.
*/

// snippet:begin
// Different values in a[l..r] for every question, answered offline: sweep the right end, keep a mark at the last occurrence of each value.
vector<int> distinctValues(vector<int> a, const vector<array<int, 2>>& queries) {
    int n = a.size();
    vector<int> sorted = a;  // compress the values to 0..m-1 so that "last position" is an array
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    for (int& x : a) x = lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
    vector<int> tree(n + 1, 0), last(sorted.size(), 0);  // last[v] = position of the last v so far, 0 if none
    auto add = [&](int i, int d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    };
    auto prefix = [&](int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    };
    vector<vector<int>> endingAt(n + 1);  // the questions grouped by their right end
    for (int q = 0; q < (int)queries.size(); q++) endingAt[queries[q][1]].push_back(q);
    vector<int> answer(queries.size());
    for (int r = 1; r <= n; r++) {
        if (last[a[r - 1]]) add(last[a[r - 1]], -1);  // the old last occurrence stops counting
        last[a[r - 1]] = r;
        add(r, 1);
        for (int q : endingAt[r]) answer[q] = prefix(r) - prefix(queries[q][0] - 1);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> queries(q);
    for (auto& [l, r] : queries) cin >> l >> r;
    for (int x : distinctValues(a, queries)) cout << x << "\n";
}
