#include <bits/stdc++.h>
using namespace std;

long long shares(int K, const vector<int>& caps) {
    vector<long long> dp(K + 1, 0), prefix(K + 2, 0);
    dp[0] = 1;
    for (int cap : caps) {
        for (int j = 0; j <= K; j++) prefix[j + 1] = prefix[j] + dp[j];
        for (int j = 0; j <= K; j++) dp[j] = prefix[j + 1] - prefix[max(0, j - cap)];
    }
    return dp[K];
}
int main() {
    // P1: 3 candies for children who take at most 2, 1 and 2. Brute: every split. Method: ranges of the previous row by prefix sums.
    long long brute = 0;
    for (int a = 0; a <= 2; a++) for (int b = 0; b <= 1; b++) for (int c = 0; c <= 2; c++) brute += a + b + c == 3;
    cout << "P1 brute=" << brute << " method=" << shares(3, {2, 1, 2}) << '\n';
    // N1: f(1) = 1 and f(n) = f(d) summed over the divisors d < n of n, for n = 12, with the contiguous range 1..n/2.
    vector<long long> f(13, 0);
    f[1] = 1;
    for (int n = 2; n <= 12; n++) for (int d = 1; d < n; d++) if (n % d == 0) f[n] += f[d];
    long long range = 0;
    for (int d = 1; d <= 6; d++) range += f[d];
    cout << "N1 brute=" << f[12] << " method=" << range << '\n';
}
