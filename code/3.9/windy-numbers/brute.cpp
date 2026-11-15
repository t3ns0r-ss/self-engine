// Brute force: check every x in [A, B].
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    long long count = 0;
    for (long long x = a; x <= b; x++) {
        string s = to_string(x);
        bool ok = true;
        for (size_t i = 1; i < s.size(); i++) ok = ok && abs(s[i] - s[i - 1]) >= 2;
        count += ok;
    }
    cout << count << "\n";
}
