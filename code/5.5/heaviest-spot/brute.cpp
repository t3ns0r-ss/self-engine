#include <bits/stdc++.h>
using namespace std;

// Reference: try every integer point of the small grid and add up the weights of the rectangles that contain it.
int main() {
    int n;
    cin >> n;
    vector<array<long long, 5>> rects(n);
    for (auto& r : rects) cin >> r[0] >> r[1] >> r[2] >> r[3] >> r[4];
    long long bestWeight = 0, bestX = 0, bestY = 0;
    for (int x = 0; x <= 12; x++)
        for (int y = 0; y <= 12; y++) {
            long long sum = 0;
            for (auto& r : rects)
                if (r[0] <= x && x <= r[2] && r[1] <= y && y <= r[3]) sum += r[4];
            if (sum > bestWeight) bestWeight = sum, bestX = x, bestY = y;  // strictly greater: the first point in (x, y) order stays
        }
    cout << bestWeight << " " << bestX << " " << bestY << "\n";
}
