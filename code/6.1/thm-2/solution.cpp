#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.1.2. For two strings u, v of equal length (letters are numbers in 0..p-1), p prime:
// how many bases B in 0..p-1 give the same hash? The theorem says at most (length - 1) when u != v.
int badBases(const vector<int>& u, const vector<int>& v, int p) {
    int bad = 0;
    for (int B = 0; B < p; B++) {
        long long hu = 0, hv = 0;
        for (size_t i = 0; i < u.size(); i++) {
            hu = (hu * B + u[i]) % p;  // Horner's rule: hash of the prefix times B plus the next letter
            hv = (hv * B + v[i]) % p;
        }
        if (hu == hv) bad++;
    }
    return bad;
}
// snippet:end

int main() {
    cout << "p=11 [1,2] vs [2,1]: " << badBases({1, 2}, {2, 1}, 11) << "\n";
    cout << "p=11 [1,0,2] vs [2,0,1]: " << badBases({1, 0, 2}, {2, 0, 1}, 11) << "\n";
    cout << "p=11 [1,2] vs [1,3]: " << badBases({1, 2}, {1, 3}, 11) << "\n";
    cout << "p=7 [1,0,0,0] vs [0,0,0,1]: " << badBases({1, 0, 0, 0}, {0, 0, 0, 1}, 7) << "\n";
    // Check (not printed): for every prime p in {2, 3, 5, 7}, every pair of different strings of
    // length 1..4 over 0..p-1 has at most length - 1 bad bases.
    for (int p : {2, 3, 5, 7})
        for (int m = 1; m <= 4; m++) {
            int total = 1;
            for (int i = 0; i < m; i++) total *= p;
            for (int a = 0; a < total; a++)
                for (int b = 0; b < total; b++) {
                    if (a == b) continue;
                    vector<int> u(m), v(m);
                    for (int i = 0, x = a, y = b; i < m; i++, x /= p, y /= p) u[i] = x % p, v[i] = y % p;
                    if (badBases(u, v, p) > m - 1) return 1;
                }
        }
}
