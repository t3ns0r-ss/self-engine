#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    for (int L = n - 1; L >= 1; L--)
        for (int i = 0; i + L <= n; i++)
            for (int j = i + 1; j + L <= n; j++)
                if (s.compare(i, L, s, j, L) == 0) {
                    cout << s.substr(i, L) << "\n";
                    return 0;
                }
    cout << "-1\n";
}
