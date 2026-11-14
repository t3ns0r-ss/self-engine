#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int count = 0;
    for (int i = 0; i + (int)t.size() <= (int)s.size(); i++) {
        bool same = true;
        for (int j = 0; j < (int)t.size(); j++)
            if (s[i + j] != t[j]) same = false;
        if (same) count++;
    }
    cout << count << "\n";
}
