#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the smallest difference between two of 10 1 7 3 8. Brute: all pairs. Method: neighbours after sorting.
    vector<int> a = {10, 1, 7, 3, 8};
    int brute = INT_MAX, method = INT_MAX;
    for (int i = 0; i < 5; i++) for (int j = i + 1; j < 5; j++) brute = min(brute, abs(a[i] - a[j]));
    vector<int> s = a;
    sort(s.begin(), s.end());
    for (int i = 0; i + 1 < 5; i++) method = min(method, s[i + 1] - s[i]);
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: the smallest difference between elements at least 2 positions apart in 4 5 9.
    vector<int> b = {4, 5, 9};
    brute = INT_MAX, method = INT_MAX;
    for (int i = 0; i < 3; i++) for (int j = i + 2; j < 3; j++) brute = min(brute, abs(b[i] - b[j]));
    s = b;
    sort(s.begin(), s.end());
    for (int i = 0; i + 1 < 3; i++) method = min(method, s[i + 1] - s[i]);
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: the smallest difference between elements adjacent in the input 4 9 5.
    vector<int> c = {4, 9, 5};
    brute = INT_MAX, method = INT_MAX;
    for (int i = 0; i + 1 < 3; i++) brute = min(brute, abs(c[i] - c[i + 1]));
    s = c;
    sort(s.begin(), s.end());
    for (int i = 0; i + 1 < 3; i++) method = min(method, s[i + 1] - s[i]);
    cout << "N2 brute=" << brute << " method=" << method << '\n';
}
