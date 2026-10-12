#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.7.3. The numbers 1 ... n can be split into two sets of equal sum exactly when n (n + 1) / 2 is even. Go from n down to 1 and put j
// into the first set if j is at most the part of the half-sum that is still missing. Returns the first set (empty if there is no split).
vector<int> halfOfSum(int n) {
    long long total = (long long)n * (n + 1) / 2;
    if (total % 2 != 0) return {};
    long long missing = total / 2;
    vector<int> first;
    for (int j = n; j >= 1; j--)
        if (j <= missing) {
            first.push_back(j);
            missing -= j;
        }
    return first;
}
// snippet:end

bool bruteExists(int n) {  // a subset-sum table
    int total = n * (n + 1) / 2;
    vector<bool> can(total + 1, false);
    can[0] = true;
    for (int j = 1; j <= n; j++)
        for (int s = total; s >= j; s--) can[s] = can[s] || can[s - j];
    return total % 2 == 0 && can[total / 2];
}

int main() {
    for (int n : {3, 7, 5}) {
        auto first = halfOfSum(n);
        cout << "n = " << n << ":";
        if (first.empty()) cout << " no split";
        else {
            cout << " first set";
            for (int x : first) cout << " " << x;
        }
        cout << "\n";
    }
    // Check (not printed): n = 1 to 60: a split exists exactly when the table says so, and the first set has the half-sum.
    for (int n = 1; n <= 60; n++) {
        auto first = halfOfSum(n);
        if (first.empty() != !bruteExists(n)) return 1;
        long long sum = 0;
        set<int> distinct(first.begin(), first.end());
        for (int x : first) sum += x;
        if (!first.empty() && (sum * 2 != (long long)n * (n + 1) / 2 || distinct.size() != first.size())) return 1;
    }
}
