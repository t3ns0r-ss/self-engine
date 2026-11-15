#include <bits/stdc++.h>
using namespace std;

/*
Problem: n different points in the plane. Count the lines that pass through at least k of them; print Infinity when there are infinitely many.
Input: n k, then n lines x y.
Output: the number of lines, or Infinity.
*/

// snippet:begin
struct Point { long long x, y; };
long long cross(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
// Lines through at least k of the points, or -1 when there are infinitely many (k = 1: every point has endless lines through it).
long long countLines(const vector<Point>& p, int k) {
    int n = p.size();
    if (k == 1) return -1;
    long long lines = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int onLine = 2;     // p[i] and p[j] themselves
            bool first = true;  // a line is counted once, at its two points with the smallest numbers
            for (int m = 0; m < n; m++) {
                if (m == i || m == j || cross(p[i], p[j], p[m]) != 0) continue;
                if (m < j) first = false;  // a point with a smaller number than j is on this line: it was counted before
                else onLine++;
            }
            if (first && onLine >= k) lines++;
        }
    return lines;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<Point> p(n);
    for (auto& q : p) cin >> q.x >> q.y;
    long long ans = countLines(p, k);
    if (ans < 0) cout << "Infinity\n";
    else cout << ans << "\n";
}
