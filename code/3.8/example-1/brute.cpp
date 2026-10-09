// Brute force: check every x from 1 to K (the generator keeps K small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    int d;
    cin >> k >> d;
    long long count = 0;
    for (long long x = 1; x <= k; x++) {
        int s = 0;
        for (char c : to_string(x)) s += c - '0';
        count += s % d == 0;
    }
    cout << count % 1'000'000'007 << "\n";
}
