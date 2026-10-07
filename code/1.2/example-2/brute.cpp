// Simulates the water level by level: at height t, a cell holds water if its bar is below t and
// some bar of height at least t stands on each side of it.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    int top = *max_element(h.begin(), h.end());
    long long water = 0;
    for (int t = 1; t <= top; t++)
        for (int i = 0; i < n; i++) {
            if (h[i] >= t) continue;
            bool leftWall = false, rightWall = false;
            for (int j = 0; j < i; j++) leftWall |= h[j] >= t;
            for (int j = i + 1; j < n; j++) rightWall |= h[j] >= t;
            water += leftWall && rightWall;
        }
    cout << water << "\n";
}
