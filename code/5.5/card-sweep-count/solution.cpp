#include <bits/stdc++.h>
using namespace std;

// Card unit for "Count over a sweep with a Fenwick tree". Each line prints the brute-force answer and the answer of the card's
// method for one inline example, in the order of the examples in the topic file.

// The method for points in a rectangle: sort by x, a Fenwick tree over y (Theorem 5.5.4). One rectangle, closed.
int countInside(vector<pair<int, int>> points, array<int, 4> rect) {
    auto G = [&](int X, int Y) {  // points with x <= X and y <= Y, found by adding the points in x order
        vector<int> tree(64, 0);
        sort(points.begin(), points.end());
        for (auto& [x, y] : points)
            if (x <= X)
                for (int i = y; i < 64; i += i & -i) tree[i]++;
        int sum = 0;
        for (int i = min(Y, 63); i > 0; i -= i & -i) sum += tree[i];
        return sum;
    };
    auto [a, b, c, d] = rect;
    return G(b, d) - G(a - 1, d) - G(b, c - 1) + G(a - 1, c - 1);
}

// The method for crossings: open, ask, close in that order at one x (Theorem 5.5.4 with segments).
long long crossings(const vector<array<int, 4>>& segs) {
    vector<int> alive(64, 0);  // alive[y] = horizontal segments at height y that are open now
    vector<array<int, 4>> events;
    for (auto& s : segs) {
        if (s[1] == s[3]) events.push_back({s[0], 0, s[1], 0}), events.push_back({s[2], 2, s[1], 0});
        else events.push_back({s[0], 1, s[1], s[3]});
    }
    sort(events.begin(), events.end());
    long long total = 0;
    for (auto& [x, kind, a, b] : events) {
        if (kind == 0) alive[a]++;
        else if (kind == 2) alive[a]--;
        else
            for (int y = a; y <= b; y++) total += alive[y];
    }
    return total;
}

int main() {
    vector<pair<int, int>> pts = {{1, 1}, {2, 3}, {3, 2}, {3, 3}};
    int brute = 0;
    for (auto& [x, y] : pts) brute += (1 <= x && x <= 3 && 2 <= y && y <= 3);
    cout << "P1 brute=" << brute << " method=" << countInside(pts, {1, 3, 2, 3}) << "\n";
    // P2: four segments: horizontals at y = 1 and y = 3 from x = 0 to 4, verticals at x = 2 (y from 0 to 3) and x = 5 (y from 0 to 3).
    vector<array<int, 4>> segs = {{0, 1, 4, 1}, {2, 0, 2, 3}, {5, 0, 5, 3}, {0, 3, 4, 3}};
    long long pairs = 0;
    for (auto& h : segs)
        for (auto& v : segs)
            if (h[1] == h[3] && v[0] == v[2] && h[0] <= v[0] && v[0] <= h[2] && v[1] <= h[1] && h[1] <= v[3]) pairs++;
    cout << "P2 brute=" << pairs << " method=" << crossings(segs) << "\n";
    // N1: the number 5 is added, a question counts the numbers in [5, 5], then 5 is removed and the question is asked again.
    // The sweep method answers about a fixed set of points, so it counts the point 5 for both questions.
    int truth = 0, present = 0;
    present++;                    // add 5
    truth += present;             // first question: 1
    present--;                    // remove 5
    truth += present;             // second question: 0
    int fixedSet = 2 * 1;         // the point exists in the set that the sweep sees, so each question counts it
    cout << "N1 brute=" << truth << " method=" << fixedSet << "\n";
}
