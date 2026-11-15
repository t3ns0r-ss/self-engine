#include <bits/stdc++.h>
using namespace std;

// A simple polygon: corners around the centre (3,3) sorted by angle, one corner per direction, every gap less than half a turn.
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    for (int attempt = 0; attempt < 1000; attempt++) {
        int n = rng() % 7 + 3;
        vector<pair<long long, long long>> pts;
        for (int i = 0; i < n; i++) {
            pair<long long, long long> c = {(long long)(rng() % 7), (long long)(rng() % 7)};
            if (c.first != 3 || c.second != 3) pts.push_back(c);
        }
        sort(pts.begin(), pts.end(), [](auto a, auto b) { return atan2((double)a.second - 3, (double)a.first - 3) < atan2((double)b.second - 3, (double)b.first - 3); });
        auto dir = [](pair<long long, long long> a, pair<long long, long long> b) {  // cross and dot of the two vectors from the centre
            return make_pair((a.first - 3) * (b.second - 3) - (a.second - 3) * (b.first - 3), (a.first - 3) * (b.first - 3) + (a.second - 3) * (b.second - 3));
        };
        vector<pair<long long, long long>> poly;
        for (auto c : pts)
            if (poly.empty() || !(dir(poly.back(), c).first == 0 && dir(poly.back(), c).second > 0)) poly.push_back(c);
        if (poly.size() >= 3 && dir(poly.back(), poly[0]).first == 0 && dir(poly.back(), poly[0]).second > 0) poly.pop_back();
        if (poly.size() < 3) continue;
        bool ok = true;
        for (size_t i = 0; i < poly.size(); i++) ok &= dir(poly[i], poly[(i + 1) % poly.size()]).first > 0;
        if (!ok) continue;
        if (rng() % 2) reverse(poly.begin(), poly.end());
        cout << poly.size() << "\n";
        for (auto c : poly) cout << c.first << " " << c.second << "\n";
        return 0;
    }
    cout << "3\n0 0\n4 0\n0 4\n";  // fallback
}
