#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    long long total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int h = 0;
            while (j + h < n && s[i + h] == s[j + h]) h++;
            total += h;
        }
    cout << total << "\n";
}
