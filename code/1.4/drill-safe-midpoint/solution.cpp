/*
Drill (about 4 minutes). Find the smallest integer x with x / 3 >= k (integer division), searching in [0, 9*10^18].
The answer is 3k, but compute it by binary search. The trap: lo + hi passes 9.2*10^18 and overflows long long.
Input: k, 0 <= k <= 3*10^18. Output: x.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// First x in [lo, hi] where the test holds. lo + (hi - lo) / 2 never leaves [lo, hi]; (lo + hi) / 2 can.
long long firstGood(long long lo, long long hi, long long k) {
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid / 3 >= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// snippet:end

int main() {
    long long k;
    cin >> k;
    cout << firstGood(0, 9000000000000000000LL, k) << "\n";
}
