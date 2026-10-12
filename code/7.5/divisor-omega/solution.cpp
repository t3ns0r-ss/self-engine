#include <bits/stdc++.h>
using namespace std;

/*
Problem: a sequence of n numbers A_i >= 1 (n up to 2·10^5, A_i up to 10^6). A move chooses an index i and a divisor d of A_i with d < A_i and
replaces A_i by d. The player who cannot move loses; Anna moves first. Print Anna or Bruno (the winner).
Input: n, then the n numbers.
Output: Anna or Bruno.
*/


// snippet:begin
// Theorem 7.5.3: replacing A by a proper divisor removes at least one prime factor, and any number of them from 1 to Omega(A) can be removed,
// so the number A is a Nim heap of size Omega(A), its number of prime factors with repetition. A sieve of smallest primes gives Omega.
string winner(const vector<int>& a) {
    int top = *max_element(a.begin(), a.end());
    vector<int> smallest(top + 1, 0), omega(top + 1, 0);
    for (int p = 2; p <= top; p++)
        if (!smallest[p])
            for (int m = p; m <= top; m += p)
                if (!smallest[m]) smallest[m] = p;
    for (int x = 2; x <= top; x++) omega[x] = omega[x / smallest[x]] + 1;
    int total = 0;
    for (int x : a) total ^= omega[x];
    return total ? "Anna" : "Bruno";
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << winner(a) << "\n";
}
