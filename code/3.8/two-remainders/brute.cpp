// Brute force: check every x in [A, B].
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    int m, d;
    cin >> a >> b >> m >> d;
    long long count = 0;
    for (long long x = a; x <= b; x++) {
        int s = 0;
        for (char c : to_string(x)) s += c - '0';
        count += (x % m == 0 && s % d == 0);
    }
    cout << count << "\n";
}
