// Keeps every added value in a vector and scans it for each question.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    vector<int> v;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            v.push_back(x);
        } else if (type == 2) {
            int x;
            cin >> x;
            bool found = false;
            for (int y : v) found = found || y == x;
            cout << (found ? "YES" : "NO") << "\n";
        } else {
            int distinct = 0;
            for (size_t i = 0; i < v.size(); i++) {
                bool first = true;
                for (size_t j = 0; j < i; j++) first = first && v[j] != v[i];
                if (first) distinct++;
            }
            cout << distinct << "\n";
        }
    }
}
