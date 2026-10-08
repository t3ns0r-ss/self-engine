#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 1000000007;
    int N, K;
    cin >> N >> K;
    vector<int> a(N, 1);
    long long sum = 0;
    while (true) {  // every sequence, like a counter in base K
        int g = 0;
        for (int v : a) g = gcd(g, v);
        sum = (sum + g) % MOD;
        int i = 0;
        while (i < N && a[i] == K) a[i++] = 1;
        if (i == N) break;
        a[i]++;
    }
    cout << sum << "\n";
}
