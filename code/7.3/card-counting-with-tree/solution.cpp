#include <bits/stdc++.h>
using namespace std;

// method: the recurrence of the card, cnt[i] = 1 + sum of cnt[j] over earlier j with a[j] < a[i] (len = 0), or the layered one
// cnt[len][i] = sum of cnt[len - 1][j] (len > 0, the number of subsequences of exactly len elements).
long long method(const vector<int>& a, int len) {
    int n = a.size();
    vector<vector<long long>> cnt(len + 1, vector<long long>(n, 0));
    long long total = 0;
    if (len == 0) {
        for (int i = 0; i < n; i++) {
            cnt[0][i] = 1;
            for (int j = 0; j < i; j++)
                if (a[j] < a[i]) cnt[0][i] += cnt[0][j];
            total += cnt[0][i];
        }
        return total;
    }
    for (int i = 0; i < n; i++) {
        cnt[1][i] = 1;
        for (int l = 2; l <= len; l++)
            for (int j = 0; j < i; j++)
                if (a[j] < a[i]) cnt[l][i] += cnt[l - 1][j];
    }
    for (int i = 0; i < n; i++) total += cnt[len][i];
    return total;
}
// brute: all subsequences (len = 0: any length), counted if the values strictly increase; or all pairs i < j with a[i] > a[j].
long long bruteIncreasing(const vector<int>& a, int len) {
    int n = a.size();
    long long count = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (len > 0 && __builtin_popcount(mask) != len) continue;
        int last = INT_MIN;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) ok &= last < a[i], last = a[i];
        count += ok;
    }
    return count;
}
long long bruteInversions(const vector<int>& a) {
    long long count = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++) count += a[i] > a[j];
    return count;
}
int main() {
    vector<int> a1 = {3, 1, 2, 4}, a2 = {3, 1, 2};
    cout << "P1 brute=" << bruteIncreasing(a1, 0) << " method=" << method(a1, 0) << "\n";
    cout << "P2 brute=" << bruteIncreasing(a1, 2) << " method=" << method(a1, 2) << "\n";
    cout << "N1 brute=" << bruteInversions(a2) << " method=" << method(a2, 0) << "\n";
}
