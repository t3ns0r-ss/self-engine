#include <bits/stdc++.h>
using namespace std;

int digitSum(long long x) { int s = 0; for (; x > 0; x /= 10) s += x % 10; return s; }
// F(N) = how many x in [0, N] have digit sum divisible by m (state: digit sum mod m)
long long walkSumDiv(long long N, int m) {
    if (N < 0) return 0;
    string digits = to_string(N);
    int L = digits.size();
    vector<vector<long long>> memo(L + 1, vector<long long>(m, -1));
    function<long long(int, int, bool)> go = [&](int pos, int s, bool tight) -> long long {
        if (pos == L) return s == 0;
        if (!tight && memo[pos][s] != -1) return memo[pos][s];
        int hi = tight ? digits[pos] - '0' : 9;
        long long total = 0;
        for (int c = 0; c <= hi; c++) total += go(pos + 1, (s + c) % m, tight && c == hi);
        if (!tight) memo[pos][s] = total;
        return total;
    };
    return go(0, 0, true);
}
// F(N) = how many x in [0, N] have all neighbouring digits different (state: previous digit, started)
long long walkNeighbours(long long N, int minDiff) {
    if (N < 0) return 0;
    string digits = to_string(N);
    int L = digits.size();
    function<long long(int, int, bool, bool)> go = [&](int pos, int prev, bool tight, bool started) -> long long {
        if (pos == L) return 1;
        int hi = tight ? digits[pos] - '0' : 9;
        long long total = 0;
        for (int c = 0; c <= hi; c++) {
            if (!started && c == 0) { total += go(pos + 1, 10, tight && c == hi, false); continue; }
            if (prev != 10 && abs(c - prev) < minDiff) continue;
            total += go(pos + 1, c, tight && c == hi, true);
        }
        return total;
    };
    return go(0, 10, true, false);
}
int main() {
    // P1: the numbers in [1, 100] with all neighbouring digits different. P2: the numbers in [1, 100] with neighbouring digits differing by at least 2.
    long long b1 = 0, b2 = 0;
    for (int x = 1; x <= 100; x++) {
        string s = to_string(x);
        bool ok1 = true, ok2 = true;
        for (size_t i = 1; i < s.size(); i++) { ok1 &= s[i] != s[i - 1]; ok2 &= abs(s[i] - s[i - 1]) >= 2; }
        b1 += ok1, b2 += ok2;
    }
    cout << "P1 brute=" << b1 << " method=" << walkNeighbours(100, 1) - 1 << '\n';
    cout << "P2 brute=" << b2 << " method=" << walkNeighbours(100, 2) - 1 << '\n';
    // N1: the same as P1 without the started flag: the padded strings 001..009 are rejected because of "00".
    function<long long(int, int, bool)> padded = [&](int pos, int prev, bool tight) -> long long {
        string digits = "100";
        if (pos == 3) return 1;
        int hi = tight ? digits[pos] - '0' : 9;
        long long total = 0;
        for (int c = 0; c <= hi; c++) if (c != prev) total += padded(pos + 1, c, tight && c == hi);
        return total;
    };
    cout << "N1 brute=" << b1 << " method=" << padded(0, 10, true) << '\n';
}
