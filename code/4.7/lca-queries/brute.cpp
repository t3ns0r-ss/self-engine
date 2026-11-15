#include <bits/stdc++.h>
using namespace std;

// Mark the bosses of a (including a), then climb from b to the first marked employee.
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    while (q--) {
        int a, b;
        cin >> a >> b;
        vector<bool> mark(n + 1, false);
        for (int x = a; x != 0; x = parent[x]) mark[x] = true;
        int x = b;
        while (!mark[x]) x = parent[x];
        cout << x << "\n";
    }
}
