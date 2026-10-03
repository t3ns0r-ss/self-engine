// Walks the multiples of K downward from 10^6 and keeps the last one that passes.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int s, k;
    cin >> s >> k;
    int best = -1;
    for (int x = 1000000 / k * k; x >= 1; x -= k) {
        string d = to_string(x);
        int sum = 0;
        for (char ch : d) sum += ch - '0';
        if (sum == s) best = x;
    }
    cout << best << "\n";
}
