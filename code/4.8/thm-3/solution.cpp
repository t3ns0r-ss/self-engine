#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.8.3. A polygon is a list of corners in counterclockwise order (the first corner is not repeated at the end).
struct Point { long long x, y; };
// Twice the area. The sum is kept in __int128: the running total can pass 9.2*10^18 on the way, although the result fits.
long long twiceArea(const vector<Point>& p) {
    __int128 sum = 0;
    for (size_t i = 0; i < p.size(); i++) {
        Point a = p[i], b = p[(i + 1) % p.size()];
        sum += (__int128)a.x * b.y - (__int128)b.x * a.y;  // twice the signed area of the triangle (0,0), a, b
    }
    return (long long)sum;  // negative when the corners are clockwise
}
// Lattice points on the boundary: the edge from a to b holds gcd(|dx|, |dy|) of them, not counting b.
long long boundaryPoints(const vector<Point>& p) {
    long long count = 0;
    for (size_t i = 0; i < p.size(); i++) {
        Point a = p[i], b = p[(i + 1) % p.size()];
        count += __gcd(llabs(b.x - a.x), llabs(b.y - a.y));
    }
    return count;
}
// snippet:end

int main() {
    auto show = [&](const vector<Point>& p, const char* name) {
        long long s = twiceArea(p), b = boundaryPoints(p);
        cout << name << ": twice the area " << s << ", boundary points " << b << ", interior points " << (llabs(s) - b + 2) / 2 << "\n";
    };
    show({{0, 0}, {4, 0}, {4, 3}, {0, 3}}, "rectangle 4 by 3");
    show({{0, 0}, {0, 3}, {4, 3}, {4, 0}}, "the same rectangle, clockwise");
    show({{0, 0}, {5, 0}, {0, 5}}, "triangle with legs 5");
    show({{0, 0}, {4, 2}, {1, 3}}, "slanted triangle");
    show({{0, 0}, {4, 0}, {4, 2}, {2, 2}, {2, 4}, {0, 4}}, "L shape");

    // L shape: count the lattice points of the region directly.
    {
        int total = 0;
        for (int x = 0; x <= 4; x++)
            for (int y = 0; y <= 4; y++)
                if ((y <= 2) || (x <= 2)) total++;
        vector<Point> l = {{0, 0}, {4, 0}, {4, 2}, {2, 2}, {2, 4}, {0, 4}};
        if (total != (twiceArea(l) - boundaryPoints(l) + 2) / 2 + boundaryPoints(l)) return 1;
    }
    // Every triangle with corners in 0..4 (counterclockwise): count the lattice points by testing each one against the three sides.
    for (int ax = 0; ax <= 4; ax++)
        for (int ay = 0; ay <= 4; ay++)
            for (int bx = 0; bx <= 4; bx++)
                for (int by = 0; by <= 4; by++)
                    for (int cx = 0; cx <= 4; cx++)
                        for (int cy = 0; cy <= 4; cy++) {
                            long long area2 = (long long)(bx - ax) * (cy - ay) - (long long)(by - ay) * (cx - ax);
                            if (area2 <= 0) continue;  // keep counterclockwise triangles with positive area
                            vector<Point> t = {{ax, ay}, {bx, by}, {cx, cy}};
                            int inside = 0, boundary = 0;
                            for (int x = 0; x <= 4; x++)
                                for (int y = 0; y <= 4; y++) {
                                    // side tests written out by hand, without the helper functions above
                                    long long s1 = (long long)(bx - ax) * (y - ay) - (long long)(by - ay) * (x - ax);
                                    long long s2 = (long long)(cx - bx) * (y - by) - (long long)(cy - by) * (x - bx);
                                    long long s3 = (long long)(ax - cx) * (y - cy) - (long long)(ay - cy) * (x - cx);
                                    if (s1 >= 0 && s2 >= 0 && s3 >= 0) (s1 == 0 || s2 == 0 || s3 == 0 ? boundary : inside)++;
                                }
                            if (twiceArea(t) != area2) return 1;
                            if (boundaryPoints(t) != boundary) return 1;
                            if (twiceArea(t) != 2 * inside + boundary - 2) return 1;  // Pick's theorem
                        }
    // A huge polygon: the square with corners at plus and minus 10^9.
    vector<Point> big = {{-1000000000, -1000000000}, {1000000000, -1000000000}, {1000000000, 1000000000}, {-1000000000, 1000000000}};
    if (twiceArea(big) != 8000000000000000000LL) return 1;
}
