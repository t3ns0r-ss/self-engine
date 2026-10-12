#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int q;
    cin >> s >> q;
    while (q--) {
        string p;
        cin >> p;
        int count = 0, first = -1;
        for (int i = 0; i + (int)p.size() <= (int)s.size(); i++)
            if (s.compare(i, p.size(), p) == 0) {
                count++;
                if (first < 0) first = i + 1;
            }
        cout << count << " " << first << "\n";
    }
}
