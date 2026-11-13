#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    size_t p;
    while ((p = s.find("ABC")) != string::npos) s.erase(p, 3);
    cout << s << "\n";
}
