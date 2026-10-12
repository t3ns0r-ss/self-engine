#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int count = 0;
    for (size_t i = 0; i + t.size() <= s.size(); i++) count += s.compare(i, t.size(), t) == 0;
    cout << count << "\n";
}
