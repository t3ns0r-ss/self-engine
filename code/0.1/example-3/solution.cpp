/*
Problem: AtCoder ABC 48 B Between a and b ... Count the integers in [a, b] divisible by x.
Input: a b x with 0 <= a <= b <= 10^18 and 1 <= x <= 10^18.
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Integers in [a, b] divisible by x, for 0 <= a <= b <= 10^18. Multiples of x in [0, v]: v / x + 1.
long long countMultiples(long long a, long long b, long long x) {
    long long upToB = b / x + 1;
    long long belowA = (a == 0) ? 0 : (a - 1) / x + 1;  // a - 1 >= 0 here, so / is the floor
    return upToB - belowA;
}
// snippet:end

int main() {
    long long a, b, x;
    cin >> a >> b >> x;
    cout << countMultiples(a, b, x) << "\n";
}
