#include <bits/stdc++.h>
using namespace std;

/*
Problem: the judge holds n different numbers a_1 .. a_n. Find a position p whose number is smaller than both
neighbours (a position outside 1..n counts as infinitely large). Any such position is accepted.
Input: n. A question "? i" is answered with a_i. At most 2 * ceil(log2 n) questions are allowed.
Output: "! p".
*/

// snippet:begin
// Asks for a_i. endl flushes the question; -1 means the judge refused it, so quit at once.
long long valueAt(int i) {
    cout << "? " << i << endl;
    long long value;
    cin >> value;
    if (value == -1) exit(0);
    return value;
}

// Keeps a local minimum inside lo..hi: a_{lo-1} > a_lo and a_hi < a_{hi+1}.
int findLocalMin(int n) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        long long here = valueAt(mid);       // two separate statements: the order of the two
        long long next = valueAt(mid + 1);   // questions is then the same on every compiler
        if (here > next) lo = mid + 1;       // the numbers fall at mid: a local minimum is at mid + 1 or to the right
        else hi = mid;                       // the numbers rise at mid: a local minimum is at mid or to the left
    }
    return lo;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    int p = findLocalMin(n);
    cout << "! " << p << endl;
    return 0;
}
