#include <bits/stdc++.h>
using namespace std;

const long long P = (1LL << 61) - 1;
long long mulmod(long long a, long long b) { return (__int128)a * b % P; }
long long direct(const string& t, long long B) {
    long long v = 0;
    for (char c : t) v = (mulmod(v, B) + (c - 'a' + 1)) % P;
    return v;
}

// snippet:begin
// Theorem 6.1.3 (a). h is the hash of a window of length m; pwm1 = B^(m-1). Drop the first letter, add the next.
long long slideRight(long long h, int outLetter, int inLetter, long long B, long long pwm1) {
    long long without = (h + P - mulmod(outLetter, pwm1)) % P;
    return (mulmod(without, B) + inLetter) % P;
}
// Theorem 6.1.3 (b). Change the letter at place i of the window (counting from 0); pwi = B^(m-1-i).
long long replaceLetter(long long h, int oldLetter, int newLetter, long long pwi) {
    return (h + mulmod(newLetter + P - oldLetter, pwi)) % P;
}
// snippet:end

int main() {
    {
        string s = "abcde";
        long long B = 10, h = direct("abc", B), pw2 = 100;
        h = slideRight(h, 1, 4, B, pw2);
        cout << "abc -> bcd: " << h << "\n";
        h = slideRight(h, 2, 5, B, pw2);
        cout << "bcd -> cde: " << h << "\n";
    }
    cout << "bcd, place 1 c -> i: " << replaceLetter(234, 3, 9, 10) << "\n";
    cout << "bcd, place 0 b -> a: " << replaceLetter(234, 2, 1, 100) << "\n";
    // Checks (not printed): both updates equal the hash computed from scratch, on random strings and bases.
    mt19937_64 rng(777);
    for (int it = 0; it < 20000; it++) {
        int m = rng() % 8 + 1, n = m + rng() % 5;
        string s(n, 'a');
        for (char& c : s) c = 'a' + rng() % 26;
        long long B = rng() % (P - 1000) + 500;
        long long pwm1 = 1, pwi;
        for (int i = 0; i + 1 < m; i++) pwm1 = mulmod(pwm1, B);
        int l = rng() % (n - m + 1);
        long long h = direct(s.substr(l, m), B);
        if (l + m < n) {
            long long got = slideRight(h, s[l] - 'a' + 1, s[l + m] - 'a' + 1, B, pwm1);
            if (got != direct(s.substr(l + 1, m), B)) return 1;
        }
        int i = rng() % m;
        pwi = 1;
        for (int k = 0; k < m - 1 - i; k++) pwi = mulmod(pwi, B);
        char c = 'a' + rng() % 26;
        string t = s.substr(l, m);
        long long got = replaceLetter(h, t[i] - 'a' + 1, c - 'a' + 1, pwi);
        t[i] = c;
        if (got != direct(t, B)) return 1;
    }
}
