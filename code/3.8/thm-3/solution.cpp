#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.8.3. The started flag: while only zeros have been read, the state is untouched, so the rule "no two equal neighbouring
// digits" sees the digits of the number without padding. Counts 1..N; pass useFlag = false to see the padded count.
long long neighbours(long long N, bool useFlag) {
    string digits = to_string(N);
    int L = digits.size();
    function<long long(int, int, bool, bool)> go = [&](int pos, int prev, bool tight, bool started) -> long long {
        if (pos == L) return 1;
        int hi = tight ? digits[pos] - '0' : 9;
        long long total = 0;
        for (int c = 0; c <= hi; c++) {
            if (useFlag && !started && c == 0) { total += go(pos + 1, 10, tight && c == hi, false); continue; }
            if (prev != 10 && c == prev) continue;
            total += go(pos + 1, c, tight && c == hi, true);
        }
        return total;
    };
    return go(0, 10, true, false) - (useFlag ? 1 : 0);  // minus the number 0, which only the flag version counts
}
// snippet:end

int main() {
    cout << "numbers in 1..100 with all neighbouring digits different: " << neighbours(100, true) << " with the flag, " << neighbours(100, false) << " without\n";
    for (long long n = 1; n <= 400; n += 13) {
        long long brute = 0;
        for (long long x = 1; x <= n; x++) {
            string s = to_string(x);
            bool ok = true;
            for (size_t i = 1; i < s.size(); i++) if (s[i] == s[i - 1]) ok = false;
            brute += ok;
        }
        if (brute != neighbours(n, true)) return 1;
    }
}
