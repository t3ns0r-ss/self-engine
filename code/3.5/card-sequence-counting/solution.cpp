#include <bits/stdc++.h>
using namespace std;

long long run(int n, int k, int r) {
    vector<long long> cnt(r + 1, 0);
    cnt[1] = k;
    for (int len = 2; len <= n; len++) {
        long long total = 0;
        for (int j = 1; j <= r; j++) total += cnt[j];
        vector<long long> next(r + 1, 0);
        next[1] = total * (k - 1);
        for (int j = 2; j <= r; j++) next[j] = cnt[j - 1];
        cnt = next;
    }
    long long a = 0;
    for (int j = 1; j <= r; j++) a += cnt[j];
    return a;
}
long long noAb(int n) {
    long long a = 1, other = 2;
    for (int len = 2; len <= n; len++) { long long na = a + other, no = a + 2 * other; a = na, other = no; }
    return a + other;
}
int main() {
    // P1: the strings of length 3 over {a, b, c} with no "ab". P2: the binary strings of length 4 with no letter 3 times in a row.
    long long b1 = 0;
    for (int code = 0; code < 27; code++) {
        string s;
        int x = code;
        for (int i = 0; i < 3; i++) s += 'a' + x % 3, x /= 3;
        b1 += s.find("ab") == string::npos;
    }
    cout << "P1 brute=" << b1 << " method=" << noAb(3) << '\n';
    int b2 = 0;
    for (int code = 0; code < 16; code++) {
        bool ok = true;
        for (int i = 0; i + 2 < 4; i++) {
            int a = code >> i & 1, b = code >> (i + 1) & 1, c = code >> (i + 2) & 1;
            if (a == b && b == c) ok = false;
        }
        b2 += ok;
    }
    cout << "P2 brute=" << b2 << " method=" << run(4, 2, 2) << '\n';
    // N1: the strings of length 3 over {a, b, c} with all letters different, with only the last letter as the state (no equal neighbours).
    int b3 = 0, neighbours = 0;
    for (int code = 0; code < 27; code++) {
        int x = code % 3, y = code / 3 % 3, z = code / 9;
        b3 += x != y && y != z && x != z;
        neighbours += x != y && y != z;
    }
    cout << "N1 brute=" << b3 << " method=" << neighbours << '\n';
}
