#include <bits/stdc++.h>
using namespace std;

long long best;
void go(vector<int>& v, int k) {
    if (k == 0) return void(best = min(best, (long long)accumulate(v.begin(), v.end(), 0LL)));
    for (size_t i = 0; i < v.size(); i++) {
        int old = v[i];
        v[i] -= old / 2;
        go(v, k - 1);
        v[i] = old;
    }
}
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> piles(n);
    for (int& x : piles) cin >> x;
    best = LLONG_MAX;
    go(piles, k);
    cout << best << "\n";
}
