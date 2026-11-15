// Brute force: add the digit sums of every x in [A, B].
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    long long total = 0;
    for (long long x = a; x <= b; x++)
        for (char c : to_string(x)) total += c - '0';
    cout << total % 1'000'000'007 << "\n";
}
