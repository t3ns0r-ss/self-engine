#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.3. The sum and the maximum of every window of exactly k elements: add a[r], remove a[r - k].
vector<long long> windowSums(const vector<long long>& a, int k) {
    vector<long long> out;
    long long sum = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        if (r >= k) sum -= a[r - k];
        if (r >= k - 1) out.push_back(sum);
    }
    return out;
}

vector<long long> windowMax(const vector<long long>& a, int k) {
    multiset<long long> window;  // a plain maximum cannot remove; a multiset can
    vector<long long> out;
    for (int r = 0; r < (int)a.size(); r++) {
        window.insert(a[r]);
        if (r >= k) window.erase(window.find(a[r - k]));  // one copy only
        if (r >= k - 1) out.push_back(*window.rbegin());
    }
    return out;
}
// snippet:end

int main() {
    for (vector<long long> a : {vector<long long>{5, 1, 2, 4}, vector<long long>{3, 1, 2, 1, 4, 1}}) {
        for (long long x : a) cout << x << ' ';
        cout << ", k = 3: sums";
        for (long long x : windowSums(a, 3)) cout << ' ' << x;
        cout << "; maxima";
        for (long long x : windowMax(a, 3)) cout << ' ' << x;
        cout << '\n';
    }
    mt19937 rng(3);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8 + 1, k = rng() % n + 1;
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 9) - 4;
        vector<long long> s, m;
        for (int l = 0; l + k <= n; l++) {
            s.push_back(accumulate(a.begin() + l, a.begin() + l + k, 0LL));
            m.push_back(*max_element(a.begin() + l, a.begin() + l + k));
        }
        if (s != windowSums(a, k) || m != windowMax(a, k)) return 1;
    }
}
