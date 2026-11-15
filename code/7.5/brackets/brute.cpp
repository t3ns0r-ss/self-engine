#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    vector<pair<int, int>> costs(count(s.begin(), s.end(), '?'));
    for (auto& [a, b] : costs) cin >> a >> b;
    int q = costs.size();
    long long best = -1;
    for (int mask = 0; mask < (1 << q); mask++) {
        int balance = 0, question = 0;
        long long total = 0;
        bool ok = true;
        for (char c : s) {
            if (c == '?') {
                bool open = mask >> question & 1;
                total += open ? costs[question].first : costs[question].second;
                balance += open ? 1 : -1, question++;
            } else balance += c == '(' ? 1 : -1;
            ok &= balance >= 0;
        }
        if (ok && balance == 0 && (best < 0 || total < best)) best = total;
    }
    cout << best << "\n";
}
