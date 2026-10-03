// Tries every d from 1 to N (the generator keeps N small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    for (long long d = 1; d <= n; d++)
        if (n % d == 0) cout << d << " ";
    cout << "\n";
}
