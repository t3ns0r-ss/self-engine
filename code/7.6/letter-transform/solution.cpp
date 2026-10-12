#include <bits/stdc++.h>
using namespace std;

/*
Problem: a lowercase string s and a number t. In one transformation every letter c is replaced by the next nums[c] letters of the alphabet
(cyclically; "z" is followed by "a"). Print the length of the string after t transformations, modulo 10^9 + 7.
Input: the string s, the number t (up to 10^9), then the 26 numbers nums[0..25] (each from 1 to 25).
Output: the length modulo 10^9 + 7.
*/

const long long MOD = 1000000007;
using Matrix = vector<vector<long long>>;
Matrix multiply(const Matrix& a, const Matrix& b, long long mod) {
    int n = a.size();
    Matrix c(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
    return c;
}
Matrix power(Matrix base, long long e, long long mod) {  // base^e: start from the identity, then repeated squaring
    int n = base.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1 % mod;
    for (; e > 0; e >>= 1, base = multiply(base, base, mod))
        if (e & 1) result = multiply(result, base, mod);
    return result;
}

// snippet:begin
// Theorem 7.6.2: one step sends every letter i to the next nums[i] letters: step[i][j] = 1 if j is one of them. The walks of length t from
// the letter of each character count the letters, so the length is the sum of the entries of the rows of step^t that belong to s.
long long finalLength(const string& s, long long t, const vector<int>& nums) {
    Matrix step(26, vector<long long>(26, 0));
    for (int i = 0; i < 26; i++)
        for (int d = 1; d <= nums[i]; d++) step[i][(i + d) % 26] = 1;
    Matrix p = power(step, t, MOD);
    long long total = 0;
    for (char ch : s)
        for (int j = 0; j < 26; j++) total = (total + p[ch - 'a'][j]) % MOD;
    return total;
}
// snippet:end

int main() {
    string s;
    long long t;
    cin >> s >> t;
    vector<int> nums(26);
    for (int& x : nums) cin >> x;
    cout << finalLength(s, t, nums) << "\n";
}
