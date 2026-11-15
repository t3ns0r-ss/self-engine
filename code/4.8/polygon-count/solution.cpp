#include <bits/stdc++.h>
using namespace std;

/*
Problem: a simple polygon with integer corners (listed in either direction, up to 10^9 in absolute value). Find twice its area,
the number of lattice points on its boundary, and the number of lattice points strictly inside.
Input: n, then n lines x y.
Output: three numbers: twice the area, the boundary count, the interior count.
*/

// snippet:begin
struct Point { long long x, y; };
// Returns {twice the area, lattice points on the boundary, lattice points inside}.
array<long long, 3> latticeCounts(const vector<Point>& p) {
    __int128 sum = 0;  // twice the signed area; __int128 because the running total can pass 9.2*10^18
    long long boundary = 0;
    for (size_t i = 0; i < p.size(); i++) {
        Point a = p[i], b = p[(i + 1) % p.size()];
        sum += (__int128)a.x * b.y - (__int128)b.x * a.y;
        boundary += __gcd(llabs(b.x - a.x), llabs(b.y - a.y));  // llabs: gcd of a negative number is not what we want
    }
    long long twice = (long long)(sum < 0 ? -sum : sum);        // clockwise corners give a negative sum
    return {twice, boundary, (twice - boundary + 2) / 2};       // Pick's theorem: 2A = 2I + B - 2
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& q : p) cin >> q.x >> q.y;
    auto r = latticeCounts(p);
    cout << r[0] << " " << r[1] << " " << r[2] << "\n";
}
