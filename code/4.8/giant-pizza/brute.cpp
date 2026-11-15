#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 2>> wish(n), sign(n);
    for (int i = 0; i < n; i++) {
        char s1, s2;
        cin >> s1 >> wish[i][0] >> s2 >> wish[i][1];
        sign[i] = {s1 == '+', s2 == '+'};
    }
    for (int mask = 0; mask < (1 << m); mask++) {  // bit x - 1 says whether topping x is on the pizza
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            bool any = false;
            for (int k = 0; k < 2; k++) any = any || (((mask >> (wish[i][k] - 1)) & 1) == sign[i][k]);
            ok = any;
        }
        if (ok) {
            cout << "POSSIBLE\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
