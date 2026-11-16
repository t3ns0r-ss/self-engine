/*
Drill (about 3 minutes). The input is a list of integers separated by spaces and newlines, and nobody says how many.
Print three numbers on one line: how many there are, their sum, and the largest. The input has at least one number.
Input: up to 2*10^5 integers, each with absolute value at most 10^9.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Read until the stream fails: `cin >> x` is false at the end of the input, so the loop needs no count.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long x, sum = 0, best = LLONG_MIN;
    int count = 0;
    while (cin >> x) {
        count++;
        sum += x;
        best = max(best, x);
    }
    cout << count << " " << sum << " " << best << "\n";
}
// snippet:end
