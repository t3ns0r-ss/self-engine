#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.2. Counting with a state: strings over {a, b, c} with no "ab" inside. The rule only looks at whether the previous
// letter is a, so two states are enough: ends with a, and other.
vector<array<long long, 3>> countStrings(int maxLen) {
    vector<array<long long, 3>> table;  // {ends with a, other, total}
    long long a = 1, other = 2;  // length 1
    table.push_back({a, other, a + other});
    for (int len = 2; len <= maxLen; len++) {
        long long newA = a + other;      // append a to anything
        long long newOther = a + 2 * other;  // after a only c; after other, b or c
        a = newA, other = newOther;
        table.push_back({a, other, a + other});
    }
    return table;
}
// snippet:end

int main() {
    auto t = countStrings(4);
    cout << "length: ends with a, other, total\n";
    for (int i = 0; i < 4; i++) cout << i + 1 << ": " << t[i][0] << ", " << t[i][1] << ", " << t[i][2] << '\n';
    for (int len = 1; len <= 8; len++) {
        long long brute = 0, total = 1;
        for (int i = 0; i < len; i++) total *= 3;
        for (long long code = 0; code < total; code++) {
            string s;
            long long x = code;
            for (int i = 0; i < len; i++) s += 'a' + x % 3, x /= 3;
            brute += s.find("ab") == string::npos;
        }
        if (brute != countStrings(8)[len - 1][2]) return 1;
    }
}
