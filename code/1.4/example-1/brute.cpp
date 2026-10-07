// Tries every triple and checks the three inequalities directly.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> L(n);
    for (auto& x : L) cin >> x;
    long long count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++) {
                int a = L[i], b = L[j], c = L[k];
                count += a < b + c && b < c + a && c < a + b;
            }
    cout << count << "\n";
}
