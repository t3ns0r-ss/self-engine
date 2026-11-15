#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.6.1. Twice the signed area of the triangle A, B, C.
// Positive: C is left of the line from A to B. Negative: right. Zero: A, B and C are on one line.
struct Point { long long x, y; };  // long long: coordinates up to 10^9, so differences reach 2*10^9
long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
// snippet:end

int main() {
    auto show = [&](Point a, Point b, Point c, const char* note) {
        cout << "A=(" << a.x << "," << a.y << ") B=(" << b.x << "," << b.y << ") C=(" << c.x << "," << c.y << "): cross = " << cross(a, b, c)
             << " (" << note << ")\n";
    };
    show({0, 0}, {4, 0}, {1, 3}, "C is left of AB, twice the area");
    show({0, 0}, {2, 2}, {3, 3}, "collinear");
    show({0, 0}, {4, 0}, {1, -3}, "C is right of AB");
    show({-1000000000, -1000000000}, {1000000000, -1000000000}, {-1000000000, 1000000000}, "largest coordinates, still fits");

    // Check the claim on every triple of points with coordinates in -2..2, with two methods that do not use the formula:
    // a search for a common line a*x + b*y = c, and the angle from AB to AC.
    vector<Point> grid;
    for (int x = -2; x <= 2; x++)
        for (int y = -2; y <= 2; y++) grid.push_back({x, y});
    for (Point a : grid)
        for (Point b : grid)
            for (Point c : grid) {
                bool online = false;
                for (int p = -4; p <= 4 && !online; p++)
                    for (int q = -4; q <= 4 && !online; q++) {
                        if (p == 0 && q == 0) continue;
                        for (int r = -40; r <= 40; r++)
                            if (p * a.x + q * a.y == r && p * b.x + q * b.y == r && p * c.x + q * c.y == r) { online = true; break; }
                    }
                int want;
                if (online) want = 0;
                else {
                    double t = atan2((double)(c.y - a.y), (double)(c.x - a.x)) - atan2((double)(b.y - a.y), (double)(b.x - a.x));
                    while (t > M_PI) t -= 2 * M_PI;
                    while (t <= -M_PI) t += 2 * M_PI;
                    want = t > 0 ? 1 : -1;
                }
                long long v = cross(a, b, c);
                int got = (v > 0) - (v < 0);
                if (got != want) return 1;
            }
}
