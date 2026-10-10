#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the pairs i < j with equal values in 3 1 3 3. Brute: all pairs. Method: counts before each increment.
    vector<int> a = {3, 1, 3, 3};
    int brute = 0, method = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) brute += a[i] == a[j];
    map<int, int> cnt;
    for (int x : a) { method += cnt[x]; cnt[x]++; }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the value of 2 5 9 closest to 6. Brute: the smallest distance. Method: the exact key 6 in a map (none: -1).
    vector<int> s = {2, 5, 9};
    int best = s[0];
    for (int v : s) if (abs(v - 6) < abs(best - 6)) best = v;
    map<int, int> c2;
    for (int v : s) c2[v]++;
    cout << "N1 brute=" << best << " method=" << (c2.count(6) ? 6 : -1) << '\n';
    // N2: the size of the map of 3 1 3 3 after asking about the absent keys 7, 8 and 9 with [].
    map<int, int> m;
    for (int x : a) m[x]++;
    size_t proper = m.size();
    for (int key : {7, 8, 9}) (void)m[key];
    cout << "N2 brute=" << proper << " method=" << m.size() << '\n';
}
