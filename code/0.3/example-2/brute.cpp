// For each comma, counts the quotes before it: an odd count means it is enclosed.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    string t = s;
    for (int i = 0; i < n; i++)
        if (s[i] == ',' && count(s.begin(), s.begin() + i, '"') % 2 == 0) t[i] = '.';
    cout << t << "\n";
}
