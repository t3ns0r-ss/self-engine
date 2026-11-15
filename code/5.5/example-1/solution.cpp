#include <bits/stdc++.h>
using namespace std;

/*
Problem (Codeforces 220B, Little Elephant and Array): n numbers and m questions (l, r); for each question print how many numbers x
occur exactly x times among a_l..a_r (1-based).
Input: n m, the n numbers, then m lines l r.
Output: the answer to each question on its own line.
*/

// snippet:begin
// A number x can occur exactly x times in a range only if it occurs at least x times in the whole array; there are at most sqrt(2n)
// such numbers. For each of them one pass builds prefix counts, and every question looks at two of them.
vector<int> elephant(const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size();
    vector<int> total(n + 1, 0), answer(queries.size(), 0), prefix(n + 1, 0);
    for (int x : a)
        if (x <= n) total[x]++;
    for (int x = 1; x <= n; x++) {
        if (total[x] < x) continue;  // x cannot reach x occurrences anywhere
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + (a[i] == x);
        for (size_t j = 0; j < queries.size(); j++) answer[j] += prefix[queries[j][1]] - prefix[queries[j][0] - 1] == x;  // 1-based l, r
    }
    return answer;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> queries(m);
    for (auto& [l, r] : queries) cin >> l >> r;
    for (int x : elephant(a, queries)) cout << x << "\n";
}
