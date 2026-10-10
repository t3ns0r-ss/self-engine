#include <bits/stdc++.h>
using namespace std;

int firstAtLeast(const vector<int>& a, int x) {
    int lo = -1, hi = a.size();
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    // P1: the number of elements at most 5 in 1 3 3 5 8. Brute: count. Method: the upper bound, firstAtLeast(6).
    vector<int> a = {1, 3, 3, 5, 8};
    int brute = 0;
    for (int x : a) brute += x <= 5;
    cout << "P1 brute=" << brute << " method=" << firstAtLeast(a, 6) << '\n';
    // N1: the first index with a_i >= 5 in the UNSORTED 8 1 5 3 (the first element already qualifies).
    vector<int> b = {8, 1, 5, 3};
    int first = 0;
    while (b[first] < 5) first++;
    cout << "N1 brute=" << first << " method=" << firstAtLeast(b, 5) << '\n';
    // N2: the first x in 1..8 with x % 3 == 0, found by binary search although the predicate is not monotone.
    int lo = 0, hi = 9;
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (mid % 3 == 0) hi = mid;
        else lo = mid;
    }
    cout << "N2 brute=" << 3 << " method=" << hi << '\n';
}
