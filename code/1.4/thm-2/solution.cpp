#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.2. In a sorted array: the lower bound (the number of elements < x), the upper bound (the number <= x),
// and the number of elements in [L, R].
int lowerBound(const vector<int>& a, int x) {
    int lo = -1, hi = a.size();  // a[lo] < x, a[hi] >= x
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid;
    }
    return hi;
}
int upperBound(const vector<int>& a, int x) { return lowerBound(a, x + 1); }
int countInRange(const vector<int>& a, int L, int R) { return upperBound(a, R) - lowerBound(a, L); }
// snippet:end

int main() {
    vector<int> a = {1, 3, 3, 5, 8};
    cout << "1 3 3 5 8: lower bound of 3 is " << lowerBound(a, 3) << ", upper bound of 3 is " << upperBound(a, 3) << '\n';
    cout << "1 3 3 5 8: elements in [3, 5]: " << countInRange(a, 3, 5) << '\n';
    cout << "1 3 3 5 8: largest element at most 4 is a[" << upperBound(a, 4) - 1 << "] = " << a[upperBound(a, 4) - 1] << '\n';
    mt19937 rng(1);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8;
        vector<int> b(n);
        for (int& x : b) x = rng() % 10;
        sort(b.begin(), b.end());
        for (int x = -1; x <= 10; x++) {
            int less = 0, atMost = 0;
            for (int y : b) less += y < x, atMost += y <= x;
            if (lowerBound(b, x) != less || upperBound(b, x) != atMost) return 1;
        }
    }
}
