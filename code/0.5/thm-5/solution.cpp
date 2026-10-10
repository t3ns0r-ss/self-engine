#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.5. The smallest x in [lo, hi] with P(x), or -1 if there is none: test the values in order.
int smallestSatisfying(int lo, int hi, const function<bool(int)>& P) {
    for (int x = lo; x <= hi; x++)
        if (P(x)) return x;
    return -1;
}
// snippet:end

int digitSum(int x) {
    int s = 0;
    for (; x > 0; x /= 10) s += x % 10;
    return s;
}

int main() {
    cout << "smallest x in 1..100 with x * x >= 50: " << smallestSatisfying(1, 100, [](int x) { return x * x >= 50; }) << '\n';
    cout << "smallest x in 1..100 divisible by 7 with digit sum 10: " << smallestSatisfying(1, 100, [](int x) { return x % 7 == 0 && digitSum(x) == 10; }) << '\n';
    cout << "smallest x in 1..10 with x * x = 50: " << smallestSatisfying(1, 10, [](int x) { return x * x == 50; }) << '\n';
    for (int lo = 1; lo <= 20; lo++)
        for (int hi = lo; hi <= 40; hi++)
            for (int m = 2; m <= 9; m++) {
                int want = -1;
                for (int x = hi; x >= lo; x--) if (x % m == 1) want = x;
                if (smallestSatisfying(lo, hi, [m](int x) { return x % m == 1; }) != want) return 1;
            }
}
