// Same process in 128-bit arithmetic, checking that every value stays below 2^62.
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long start;
    cin >> start;
    __int128 n = start;
    vector<long long> out = {start};
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        if (n >= ((__int128)1 << 62)) return 1;  // would not fit; never happens for n <= 10^6
        out.push_back((long long)n);
    }
    for (size_t i = 0; i < out.size(); i++) cout << out[i] << (i + 1 < out.size() ? ' ' : '\n');
}
