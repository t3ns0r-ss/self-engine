#include <bits/stdc++.h>
using namespace std;

// A vertex lies on a cycle if following its arrow at most n times leads back to it.
int main() {
    int n;
    cin >> n;
    vector<int> next(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> next[i];
    int count = 0;
    for (int v = 1; v <= n; v++) {
        int u = next[v];
        for (int step = 1; step <= n && u != 0; step++) {
            if (u == v) {
                count++;
                break;
            }
            u = next[u];
        }
    }
    cout << count << "\n";
}
