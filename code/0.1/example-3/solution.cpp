/*
Problem: AtCoder ABC 48 B Between a and b ... Count the integers in [a, b] divisible by x.
Input: a b x with 0 <= a <= b <= 10^18 and 1 <= x <= 10^18.
Output: the count.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, x;  // values up to 10^18
    cin >> a >> b >> x;
    // Multiples of x in [0, v] for v >= 0: floor(v / x) + 1 (counting 0). For [a, b], subtract those in [0, a - 1].
    long long upToB = b / x + 1;
    long long belowA = (a == 0) ? 0 : (a - 1) / x + 1;  // a - 1 >= 0 here, so / is the floor
    cout << upToB - belowA << "\n";
}
