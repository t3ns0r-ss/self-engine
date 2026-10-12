#include <bits/stdc++.h>
using namespace std;

bool bruteExists(string s, int distance) {  // no two equal letters at a distance of at most `distance`
    sort(s.begin(), s.end());
    do {
        bool ok = true;
        for (size_t i = 0; i < s.size(); i++)
            for (int d = 1; d <= distance && i + d < s.size(); d++) ok = ok && s[i] != s[i + d];
        if (ok) return true;
    } while (next_permutation(s.begin(), s.end()));
    return false;
}
// method (Theorem 7.7.2): the rule on the largest count, for the neighbours only.
bool methodRule(const string& s) {
    map<char, int> count;
    for (char c : s) count[c]++;
    int most = 0;
    for (auto [c, k] : count) most = max(most, k);
    return most <= ((int)s.size() + 1) / 2;
}
int main() {
    cout << "P1 brute=" << (bruteExists("aabbc", 1) ? "yes" : "no") << " method=" << (methodRule("aabbc") ? "yes" : "no") << "\n";
    cout << "P2 brute=" << (bruteExists("aaaabbc", 1) ? "yes" : "no") << " method=" << (methodRule("aaaabbc") ? "yes" : "no") << "\n";
    // N1: aabb with no equal letters at distance 1 or 2, against the rule for distance 1
    cout << "N1 brute=" << (bruteExists("aabb", 2) ? "yes" : "no") << " method=" << (methodRule("aabb") ? "yes" : "no") << "\n";
}
