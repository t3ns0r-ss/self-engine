#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    int best = 0;
    for (int L = 1; 2 * L <= n; L++)
        for (int i = 0; i + 2 * L <= n; i++)
            for (int j = i + L; j + L <= n; j++)
                if (s.compare(i, L, s, j, L) == 0) best = L;
    cout << best << "\n";
}
