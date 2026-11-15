#include <bits/stdc++.h>
using namespace std;

// Card unit for "Sign of the cross product". Each line prints the brute-force answer and the answer of the card's method for one inline
// example, in the order of the examples in the topic file.

struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
int sign(long long v) { return (v > 0) - (v < 0); }
bool inBox(Point a, Point b, Point p) { return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y); }
bool segmentsMeet(Point a, Point b, Point c, Point d) {
    int d1 = sign(cross(a, b, c)), d2 = sign(cross(a, b, d)), d3 = sign(cross(c, d, a)), d4 = sign(cross(c, d, b));
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;
    return (d1 == 0 && inBox(a, b, c)) || (d2 == 0 && inBox(a, b, d)) || (d3 == 0 && inBox(c, d, a)) || (d4 == 0 && inBox(c, d, b));
}

int main() {
    // P1: twice the area of the triangle (0,0), (4,0), (1,3). Brute force: base times height, with the base along the x axis.
    Point a = {0, 0}, b = {4, 0}, c = {1, 3};
    long long baseTimesHeight = (b.x - a.x) * llabs(c.y - a.y);
    cout << "P1 brute=" << baseTimesHeight << " method=" << cross(a, b, c) << "\n";
    // P2: the segments (0,0)-(3,0) and (2,0)-(5,0). Brute force: look at every point (x, 0) with x in steps of one half.
    int found = 0;
    for (int twice = 0; twice <= 10; twice++) {  // the point (twice / 2, 0)
        bool onFirst = 0 <= twice && twice <= 6, onSecond = 4 <= twice && twice <= 10;
        found |= onFirst && onSecond;
    }
    cout << "P2 brute=" << found << " method=" << segmentsMeet({0, 0}, {3, 0}, {2, 0}, {5, 0}) << "\n";
    // N1: the sign of the cross product of (0,0), (4*10^9, 1), (1, 4*10^9) in 64 bits. The true value is 16*10^18 - 1, above 2^63.
    Point p = {0, 0}, q = {4000000000LL, 1}, r = {1, 4000000000LL};
    __int128 exact = (__int128)(q.x - p.x) * (r.y - p.y) - (__int128)(q.y - p.y) * (r.x - p.x);
    unsigned long long wrapped = (unsigned long long)(q.x - p.x) * (unsigned long long)(r.y - p.y) - (unsigned long long)(q.y - p.y) * (unsigned long long)(r.x - p.x);
    cout << "N1 brute=" << (exact > 0) - (exact < 0) << " method=" << sign((long long)wrapped) << "\n";
}
