#include <bits/stdc++.h>
using namespace std;

string f(double x) {
    ostringstream o;
    o << fixed << setprecision(4) << x;
    string s = o.str();
    while (s.back() == '0') s.pop_back();
    if (s.back() == '.') s.pop_back();
    return s;
}
int main() {
    // P1: the sum of the sums of all subarrays of 1 2 3. Brute: list them. Method: a[i] * (i + 1) * (n - i).
    vector<long long> a = {1, 2, 3};
    long long brute = 0, method = 0;
    for (int l = 0; l < 3; l++) for (int r = l; r < 3; r++) for (int i = l; i <= r; i++) brute += a[i];
    for (int i = 0; i < 3; i++) method += a[i] * (i + 1) * (3 - i);
    cout << "P1 brute=" << f(brute) << " method=" << f(method) << '\n';
    // N1: the largest subarray sum of 3 -5 4, computed as the total of the contributions (a sum over all subarrays).
    vector<long long> b = {3, -5, 4};
    long long best = LLONG_MIN, total = 0;
    for (int l = 0; l < 3; l++) { long long s = 0; for (int r = l; r < 3; r++) { s += b[r]; best = max(best, s); } }
    for (int i = 0; i < 3; i++) total += b[i] * (i + 1) * (3 - i);
    cout << "N1 brute=" << f(best) << " method=" << f(total) << '\n';
    // N2: the sum over all subarrays of 2 2 2 of the product of their elements, computed with the weights (i + 1)(n - i).
    vector<long long> c = {2, 2, 2};
    long long prod = 0, weighted = 0;
    for (int l = 0; l < 3; l++) { long long pr = 1; for (int r = l; r < 3; r++) { pr *= c[r]; prod += pr; } }
    for (int i = 0; i < 3; i++) weighted += c[i] * (i + 1) * (3 - i);
    cout << "N2 brute=" << f(prod) << " method=" << f(weighted) << '\n';
}
