#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.2. The XOR of a[l..r] (1-based) is P_r xor P_(l-1), and the number of subarrays with XOR k
// is the number of pairs i < j with P_i = P_j xor k.
vector<int> prefixXor(const vector<int>& a) {
    vector<int> P(a.size() + 1, 0);
    for (int i = 0; i < (int)a.size(); i++) P[i + 1] = P[i] ^ a[i];
    return P;
}
int rangeXor(const vector<int>& P, int l, int r) { return P[r] ^ P[l - 1]; }

long long countXor(const vector<int>& a, int k) {
    map<int, int> seen;
    seen[0] = 1;  // P_0 = 0
    long long count = 0;
    int P = 0;
    for (int x : a) {
        P ^= x;
        auto it = seen.find(P ^ k);
        if (it != seen.end()) count += it->second;
        seen[P]++;
    }
    return count;
}
// snippet:end

int main() {
    vector<int> a = {1, 2, 3, 4}, P = prefixXor(a);
    cout << "1 2 3 4: XOR of a[2..3] is " << rangeXor(P, 2, 3) << '\n';
    cout << "1 2 3 4: subarrays with XOR 0: " << countXor(a, 0) << '\n';
    cout << "1 2 3 4: subarrays with XOR 3: " << countXor(a, 3) << '\n';
    mt19937 rng(2);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 8 + 1, k = rng() % 8;
        vector<int> b(n);
        for (int& x : b) x = rng() % 8;
        vector<int> Q = prefixXor(b);
        long long brute = 0;
        for (int l = 1; l <= n; l++) for (int r = l, x = 0; r <= n; r++) {
            x ^= b[r - 1];
            if (x != rangeXor(Q, l, r)) return 1;
            brute += x == k;
        }
        if (brute != countXor(b, k)) return 1;
    }
}
