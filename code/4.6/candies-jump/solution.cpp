/*
Problem: putting candies (AtCoder ABC 241 E style).
Input: N K, then A_0..A_{N-1} (1 <= A_i <= 10^6). A dish starts empty; K times, put A[X mod N] more candies on it, X being the number there.
Output: the number of candies after K operations (K up to 10^12).
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.6.4 on pointers. The vertex is X mod N, the next vertex is (X + A) mod N, and the jump of 2^j steps also stores the candies it adds.
long long candiesAfter(const vector<long long>& A, long long K) {
    int N = A.size(), levels = 41;  // 2^41 > 10^12
    vector<vector<int>> next(levels, vector<int>(N));
    vector<vector<long long>> gain(levels, vector<long long>(N));
    for (int v = 0; v < N; v++) next[0][v] = (v + A[v]) % N, gain[0][v] = A[v];
    for (int j = 1; j < levels; j++)
        for (int v = 0; v < N; v++) {
            int mid = next[j - 1][v];
            next[j][v] = next[j - 1][mid];
            gain[j][v] = gain[j - 1][v] + gain[j - 1][mid];  // the candies of the first half, then of the second half
        }
    long long total = 0;
    int v = 0;
    for (int j = 0; j < levels; j++)
        if (K >> j & 1) total += gain[j][v], v = next[j][v];
    return total;
}
// snippet:end

int main() {
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> A(N);
    for (auto& a : A) cin >> a;
    cout << candiesAfter(A, K) << "\n";
}
