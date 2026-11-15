#include <bits/stdc++.h>
using namespace std;

// Card example unit: the numbers of the inline examples of the card "replies that are equations". Not shown.
// brute = the hidden numbers themselves. method = the formula of Theorem 1.8.3 applied to the replies.

int main() {
    // P1: hidden 7 2 9 4; the replies are sums, and the method restores all four numbers.
    {
        vector<long long> a = {7, 2, 9, 4};
        long long s12 = a[0] + a[1], s13 = a[0] + a[2], s23 = a[1] + a[2], s14 = a[0] + a[3];
        long long a1 = (s12 + s13 - s23) / 2;
        long long a2 = s12 - a1, a3 = s13 - a1, a4 = s14 - a1;
        cout << "P1 brute=" << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << " method=" << a1 << "," << a2 << "," << a3 << ","
             << a4 << "\n";
    }
    // N1: hidden 6 3 5; the replies are xors, and the sum formula is applied to them anyway.
    {
        vector<long long> a = {6, 3, 5};
        long long x12 = a[0] ^ a[1], x13 = a[0] ^ a[2], x23 = a[1] ^ a[2];
        long long a1 = (x12 + x13 - x23) / 2;
        cout << "N1 brute=" << a[0] << " method=" << a1 << "\n";
    }
    return 0;
}
