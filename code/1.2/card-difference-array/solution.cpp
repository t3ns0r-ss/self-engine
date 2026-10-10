#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: n = 5, add 2 on [1, 3] and 5 on [2, 4]; the array afterwards. Brute: loops. Method: difference array.
    vector<int> brute(5, 0), d(6, 0), method(5);
    for (int i = 1; i <= 3; i++) brute[i] += 2;
    for (int i = 2; i <= 4; i++) brute[i] += 5;
    d[1] += 2, d[4] -= 2, d[2] += 5, d[5] -= 5;
    for (int i = 0, cur = 0; i < 5; i++) method[i] = cur += d[i];
    string b, m;
    for (int i = 0; i < 5; i++) b += (i ? "," : "") + to_string(brute[i]), m += (i ? "," : "") + to_string(method[i]);
    cout << "P1 brute=" << b << " method=" << m << '\n';
    // P2: n = 5, add 3 on [0, 4].
    vector<int> e(6, 0);
    e[0] += 3, e[5] -= 3;
    string s;
    for (int i = 0, cur = 0; i < 5; i++) s += (i ? "," : "") + to_string(cur += e[i]);
    cout << "P2 brute=3,3,3,3,3 method=" << s << '\n';
    // N1: SET a[1..3] to 5 in 1 1 1 1 1 as "add 5 on [1, 3]".
    vector<int> t = {1, 1, 1, 1, 1}, u = t;
    for (int i = 1; i <= 3; i++) t[i] = 5, u[i] += 5;
    string tb, ub;
    for (int i = 0; i < 5; i++) tb += (i ? "," : "") + to_string(t[i]), ub += (i ? "," : "") + to_string(u[i]);
    cout << "N1 brute=" << tb << " method=" << ub << '\n';
    // N2: read a[2] after the first update (add 2 on [1, 3]) by looking at the difference array d[2] directly.
    vector<int> f(6, 0);
    f[1] += 2, f[4] -= 2;
    cout << "N2 brute=" << 2 << " method=" << f[2] << '\n';
}
