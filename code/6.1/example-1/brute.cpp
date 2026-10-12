#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    string best = s;
    for (size_t i = 1; i < s.size(); i++) best = min(best, s.substr(i) + s.substr(0, i));
    cout << best << "\n";
}
