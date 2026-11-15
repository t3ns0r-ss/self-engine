// Brute force: all n^4 quadruples (nested loops, Theorem 0.5.1).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> A(n), B(n), C(n), D(n);
    for (auto* list : {&A, &B, &C, &D}) for (auto& x : *list) cin >> x;
    long long count = 0;
    for (long long a : A) for (long long b : B) for (long long c : C) for (long long d : D) count += a + b + c + d == 0;
    cout << count << "\n";
}
