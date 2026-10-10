#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the value that appears once in 4 7 4 2 7. Brute: count each value. Method: the XOR of everything.
    vector<int> a = {4, 7, 4, 2, 7};
    int brute = -1, method = 0;
    for (int x : a) if (count(a.begin(), a.end(), x) == 1) brute = x;
    for (int x : a) method ^= x;
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the value that appears once in 2 2 2 9 (the others appear three times). Method: the XOR.
    vector<int> b = {2, 2, 2, 9};
    brute = -1, method = 0;
    for (int x : b) if (count(b.begin(), b.end(), x) == 1) brute = x;
    for (int x : b) method ^= x;
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: the value that appears once in 4 7 4 2 7, combined with OR instead of XOR.
    method = 0;
    for (int x : a) method |= x;
    cout << "N2 brute=2 method=" << method << '\n';
}
