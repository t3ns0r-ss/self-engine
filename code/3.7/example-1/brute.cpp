// Brute force: try every order of combinations by recursion on the current row of slimes.
#include <bits/stdc++.h>
using namespace std;

long long solve(vector<long long> row) {
    if (row.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i + 1 < row.size(); i++) {
        vector<long long> next(row.begin(), row.begin() + i);
        next.push_back(row[i] + row[i + 1]);
        next.insert(next.end(), row.begin() + i + 2, row.end());
        best = min(best, row[i] + row[i + 1] + solve(next));
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(a) << "\n";
}
