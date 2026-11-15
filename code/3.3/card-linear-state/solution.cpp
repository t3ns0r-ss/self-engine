#include <bits/stdc++.h>
using namespace std;

long long frogBrute(const vector<int>& h, int i = 0) {  // jumps of 1 or 2
    if (i == (int)h.size() - 1) return 0;
    long long r = LLONG_MAX;
    for (int j = i + 1; j <= min((int)h.size() - 1, i + 2); j++) r = min(r, abs(h[j] - h[i]) + frogBrute(h, j));
    return r;
}
long long frog(const vector<int>& h) {
    int n = h.size();
    vector<long long> best(n, LLONG_MAX);
    best[0] = 0;
    for (int i = 1; i < n; i++) for (int j = max(0, i - 2); j < i; j++) best[i] = min(best[i], best[j] + abs(h[i] - h[j]));
    return best[n - 1];
}
int main() {
    // P1: the frog on the heights 10 30 40 20 with jumps of 1 or 2. Brute: every jump sequence. Method: best(i) per stone.
    vector<int> h = {10, 30, 40, 20};
    cout << "P1 brute=" << frogBrute(h) << " method=" << frog(h) << '\n';
    // N1: two days, activities with points 10 1 1 on both days, never the same activity twice in a row; the state is only the day.
    vector<vector<int>> p = {{10, 1, 1}, {10, 1, 1}};
    int brute = 0, method = 0;
    for (int a = 0; a < 3; a++) for (int b = 0; b < 3; b++) if (a != b) brute = max(brute, p[0][a] + p[1][b]);
    for (int d = 0; d < 2; d++) method += *max_element(p[d].begin(), p[d].end());  // the best of each day alone
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: choose exactly 2 non-adjacent elements of 5 5 -9 with the best sum; the state is only the position.
    vector<int> a = {5, 5, -9};
    int bruteK = INT_MIN;
    for (int i = 0; i < 3; i++) for (int j = i + 2; j < 3; j++) bruteK = max(bruteK, a[i] + a[j]);
    vector<int> best(4, 0);  // best[i] = the largest sum of any number of non-adjacent elements among the first i
    for (int i = 1; i <= 3; i++) best[i] = max(best[i - 1], (i >= 2 ? best[i - 2] : 0) + a[i - 1]);
    cout << "N2 brute=" << bruteK << " method=" << best[3] << '\n';
}
