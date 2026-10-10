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
    // P1: the numbers in [0, 25] with digit sum divisible by 4. Brute: test each. Method: the tight walk.
    long long brute = 0;
    for (int x = 0; x <= 25; x++) brute += digitSum(x) % 4 == 0;
    cout << "P1 brute=" << brute << " method=" << walkSumDiv(25, 4) << '\n';
    // N1: the 4-digit PINs 0000..9999 with all digits different (leading zeros are digits): 10 * 9 * 8 * 7. The walk counts the NUMBERS up to 9999.
    long long pins = 10 * 9 * 8 * 7;
    long long numbers = 0;
    for (int x = 0; x <= 9999; x++) {
        string s = to_string(x);
        sort(s.begin(), s.end());
        numbers += adjacent_find(s.begin(), s.end()) == s.end();
    }
    cout << "N1 brute=" << pins << " method=" << numbers << '\n';
}
