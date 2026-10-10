#include <bits/stdc++.h>
using namespace std;

// A node is unsafe if some path from it reaches a node that lies on a cycle (the node itself included): closure over the arrows.
int main() {
    int n;
    cin >> n;
    vector<vector<bool>> reach(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int v;
            cin >> v;
            reach[i][v] = true;
        }
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    bool first = true;
    for (int i = 0; i < n; i++) {
        bool safe = true;
        for (int j = 0; j < n; j++)
            if ((i == j || reach[i][j]) && reach[j][j]) safe = false;
        if (safe) {
            cout << (first ? "" : " ") << i;
            first = false;
        }
    }
    cout << "\n";
}
