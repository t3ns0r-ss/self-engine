#include <bits/stdc++.h>
using namespace std;

/*
Problem: rearrange the characters of a lowercase string s (length up to 500) so that no two adjacent characters are equal, or report that it is
impossible.
Input: the string s.
Output: YES if the program built a valid rearrangement (checked inside), NO if it reports that none exists (BAD if the check fails).
*/

// snippet:begin
// Theorem 7.7.2: possible exactly when no letter occurs more than (n + 1) / 2 times. Write the letters, the most frequent first, into the
// positions 0, 2, 4, ... and then 1, 3, 5, ...
string reorganize(const string& s) {  // "" if impossible
    int n = s.size();
    map<char, int> count;
    for (char c : s) count[c]++;
    vector<pair<int, char>> order;  // (minus the count, letter)
    for (auto [c, k] : count) order.push_back({-k, c});
    sort(order.begin(), order.end());
    if (-order[0].first > (n + 1) / 2) return "";
    string result(n, '?');
    int position = 0;
    for (auto [minus, c] : order)
        for (int i = 0; i < -minus; i++) {
            result[position] = c;
            position += 2;
            if (position >= n) position = 1;
        }
    return result;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    string r = reorganize(s);
    if (r.empty()) {
        cout << "NO\n";
        return 0;
    }
    string a = s, b = r;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    bool ok = a == b;
    for (size_t i = 1; i < r.size(); i++) ok = ok && r[i] != r[i - 1];
    cout << (ok ? "YES" : "BAD") << "\n";
}
