// Keeps the elements in a vector and scans it for every query.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    vector<int> v;
    while (q--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            v.push_back(x);
        } else if (type == 2) {
            for (size_t i = 0; i < v.size(); i++)
                if (v[i] == x) {
                    v.erase(v.begin() + i);
                    break;
                }
        } else {
            int best = -1;
            for (int y : v) {
                if (type == 3 && y <= x && (best == -1 || y > best)) best = y;
                if (type == 4 && y >= x && (best == -1 || y < best)) best = y;
            }
            cout << best << "\n";
        }
    }
}
