#include <bits/stdc++.h>
using namespace std;

/*
Problem: the judge holds a 0/1 string S of length n with S_1 = 0 and S_n = 1, hidden from us.
Input: n. A question "? i" is answered with S_i. At most 20 questions are allowed.
Output: "! p" for a position p with S_p != S_{p+1}. Any such position is accepted.
*/

// snippet:begin
// Asks for S_i. endl flushes the question; -1 means the judge refused it, so quit at once.
int valueAt(int i) {
    cout << "? " << i << endl;
    int value;
    cin >> value;
    if (value == -1) exit(0);
    return value;
}

// Keeps S_lo = 0 and S_hi = 1. When hi = lo + 1 the change is between lo and hi.
int findChange(int n) {
    int lo = 1, hi = n;
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (valueAt(mid) == 0) lo = mid;
        else hi = mid;
    }
    return lo;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    int p = findChange(n);
    cout << "! " << p << endl;
    return 0;
}
