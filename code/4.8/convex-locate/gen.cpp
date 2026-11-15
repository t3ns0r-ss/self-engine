#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> P;
long long cr(P a, P b, P c) { return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first); }

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    vector<P> h;
    do {  // the strict convex hull (counterclockwise) of random points, at least three corners
        vector<P> pts;
        int n = randInt(3, 9), side = randInt(2, 6);
        for (int i = 0; i < n; i++) pts.push_back({randInt(0, side), randInt(0, side)});
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        h.clear();
        if (pts.size() < 3) continue;
        for (int pass = 0; pass < 2; pass++) {
            size_t start = h.size();
            for (P p : pts) {
                while (h.size() >= start + 2 && cr(h[h.size() - 2], h.back(), p) <= 0) h.pop_back();
                h.push_back(p);
            }
            h.pop_back();
            reverse(pts.begin(), pts.end());
        }
    } while (h.size() < 3);
    cout << h.size() << "\n";
    for (P c : h) cout << c.first << " " << c.second << "\n";
    int q = randInt(1, 25);
    cout << q << "\n";
    while (q--) cout << randInt(-1, 7) << " " << randInt(-1, 7) << "\n";
}
