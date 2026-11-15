// Brute force: check every x in [A, B] (the generator keeps the range short).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    int k;
    cin >> a >> b >> k;
    long long count = 0;
    for (long long x = a; x <= b; x++) {
        set<char> d;
        for (char c : to_string(x)) d.insert(c);
        count += (int)d.size() <= k;
    }
    cout << count << "\n";
}
