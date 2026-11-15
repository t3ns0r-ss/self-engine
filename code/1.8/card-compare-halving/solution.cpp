#include <bits/stdc++.h>
using namespace std;

// Card example unit: the numbers of the inline examples of the card "halving with comparison replies". Not shown.
// brute = the position of the smallest number (look at every position, positions counted from 1).
// method = the search of Theorem 1.8.2 for a position smaller than both neighbours.

int localMin(const vector<int>& v) {
    int n = (int)v.size();
    auto a = [&](int i) { return (i < 1 || i > n) ? INT_MAX : v[i - 1]; };
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a(mid) > a(mid + 1)) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int smallestAt(const vector<int>& v) { return (int)(min_element(v.begin(), v.end()) - v.begin()) + 1; }

int main() {
    // P1: the numbers fall and then rise, so the only local minimum is the smallest number.
    vector<int> valley = {9, 6, 4, 3, 5, 8, 10};
    cout << "P1 brute=" << smallestAt(valley) << " method=" << localMin(valley) << "\n";
    // N1: the question asks for the smallest number, but the numbers fall and rise twice.
    vector<int> twice = {1, 3, 2, 4, 0};
    cout << "N1 brute=" << smallestAt(twice) << " method=" << localMin(twice) << "\n";
    return 0;
}
