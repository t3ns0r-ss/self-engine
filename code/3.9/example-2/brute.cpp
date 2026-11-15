// Brute force: count the 1s in every number from 0 to n (the generator keeps n small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long ones = 0;
    for (long long x = 0; x <= n; x++)
        for (char c : to_string(x)) ones += c == '1';
    cout << ones << "\n";
}
