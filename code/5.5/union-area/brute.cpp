#include <bits/stdc++.h>
using namespace std;

// Reference: mark every unit cell of the small grid.
int main() {
    int n;
    cin >> n;
    set<pair<int, int>> cells;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int x = x1; x < x2; x++)
            for (int y = y1; y < y2; y++) cells.insert({x, y});
    }
    cout << cells.size() << "\n";
}
