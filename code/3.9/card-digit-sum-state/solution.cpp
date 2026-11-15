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
    // P1: the numbers in [1, 100] divisible by their own digit sum. Brute: test each. Method: for each digit sum s, a walk with (sum, value mod s).
    long long brute = 0;
    for (int x = 1; x <= 100; x++) brute += x % digitSum(x) == 0;
    long long method = 0;
    string digits = "100";
    for (int target = 1; target <= 27; target++) {
        vector<vector<vector<long long>>> memo(4, vector<vector<long long>>(target + 1, vector<long long>(target, -1)));
        function<long long(int, int, int, bool)> go = [&](int pos, int sum, int rem, bool tight) -> long long {
            if (sum > target) return 0;
            if (pos == 3) return sum == target && rem == 0;
            if (!tight && memo[pos][sum][rem] != -1) return memo[pos][sum][rem];
            int hi = tight ? digits[pos] - '0' : 9;
            long long total = 0;
            for (int c = 0; c <= hi; c++) total += go(pos + 1, sum + c, (rem * 10 + c) % target, tight && c == hi);
            if (!tight) memo[pos][sum][rem] = total;
            return total;
        };
        method += go(0, 0, 0, true);
    }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the multiples of 4 in [0, 100], counted as the numbers whose digit sum is divisible by 4.
    cout << "N1 brute=" << 100 / 4 + 1 << " method=" << walkSumDiv(100, 4) << '\n';
}
