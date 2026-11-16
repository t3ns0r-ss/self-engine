#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k;
    cin >> k;
    long long x = 0;
    while (x / 3 < k) x++;
    cout << x << "\n";
}
