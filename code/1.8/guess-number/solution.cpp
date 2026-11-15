#include <bits/stdc++.h>
using namespace std;

/*
Problem: the judge holds a hidden whole number x between 1 and n. Find it with as few questions as possible.
Input: n. A question "? m" is answered 1 when x <= m and 0 otherwise (-1 means the question was not allowed: quit).
Output: the questions, then "! x". The budget is the smallest q with 2^q >= n.
*/

// snippet:begin
// Asks whether the hidden number is at most m. endl ends the line and flushes the output;
// without the flush the question waits in the buffer and the judge never sees it.
bool atMost(long long m) {
    cout << "? " << m << endl;
    int reply;
    cin >> reply;
    if (reply == -1) exit(0);  // the judge refused the question: quit at once
    return reply == 1;
}

// Hidden number in 1..n. Keeps atMost(lo) false and atMost(hi) true, so the answer is in lo + 1 .. hi.
long long findHidden(long long n) {
    long long lo = 0, hi = n;  // long long: lo + hi can pass 2^31 when n is near 2 * 10^9
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (atMost(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    long long answer = findHidden(n);  // the questions are printed here, so the answer line must wait for it
    cout << "! " << answer << endl;
    return 0;
}
