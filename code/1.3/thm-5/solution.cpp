#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.3.5. For sorted a and b: p[i] = the number of elements of b below a[i]. j only moves forward.
vector<int> countBelow(const vector<long long>& a, const vector<long long>& b) {
    vector<int> p(a.size());
    int j = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        while (j < (int)b.size() && b[j] < a[i]) j++;
        p[i] = j;
    }
    return p;
}
// snippet:end

int main() {
    cout << "a = 2 5 5 9, b = 1 3 5 7: counts of b below each a:";
    for (int x : countBelow({2, 5, 5, 9}, {1, 3, 5, 7})) cout << ' ' << x;
    cout << '\n';
    cout << "a = 1 2, b = 5 6 7: counts of b below each a:";
    for (int x : countBelow({1, 2}, {5, 6, 7})) cout << ' ' << x;
    cout << '\n';
    mt19937 rng(5);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 6, m = rng() % 6;
        vector<long long> a(n), b(m);
        for (auto& x : a) x = rng() % 8;
        for (auto& x : b) x = rng() % 8;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        vector<int> want(n);
        for (int i = 0; i < n; i++) for (long long y : b) want[i] += y < a[i];
        if (want != countBelow(a, b)) return 1;
    }
}
