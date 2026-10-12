#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.7.2. The letters of s can be arranged with no two equal neighbours exactly when no letter occurs more than (n + 1) / 2 times.
// Write the letters, the most frequent first and equal letters together, into the positions 0, 2, 4, ... and then 1, 3, 5, ...
string arrange(const string& s) {  // "" if impossible
    int n = s.size();
    map<char, int> count;
    for (char c : s) count[c]++;
    vector<pair<int, char>> order;  // (minus the count, letter)
    for (auto [c, k] : count) order.push_back({-k, c});
    sort(order.begin(), order.end());
    if (n == 0 || -order[0].first > (n + 1) / 2) return "";
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

bool bruteExists(string s) {  // a search over all arrangements
    sort(s.begin(), s.end());
    do {
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++) ok = ok && s[i] != s[i - 1];
        if (ok) return true;
    } while (next_permutation(s.begin(), s.end()));
    return false;
}

int main() {
    for (string s : {"aab", "aaab", "aabbcc"}) {
        string r = arrange(s);
        cout << s << ": " << (r.empty() ? "none" : r) << "\n";
    }
    // Check (not printed): every string over {a, b, c} of length 1 to 8.
    for (int n = 1; n <= 8; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 3;
        for (int code = 0; code < total; code++) {
            string s;
            for (int i = 0, c = code; i < n; i++, c /= 3) s += (char)('a' + c % 3);
            string r = arrange(s);
            if (r.empty() != !bruteExists(s)) return 1;
            if (!r.empty()) {
                string a = s, b = r;
                sort(a.begin(), a.end());
                sort(b.begin(), b.end());
                if (a != b) return 1;
                for (int i = 1; i < n; i++)
                    if (r[i] == r[i - 1]) return 1;
            }
        }
    }
}
