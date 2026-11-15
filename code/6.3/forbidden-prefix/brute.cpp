#include <bits/stdc++.h>
using namespace std;

int main() {  // after each query, test every string of Y against every string of X
    int q;
    cin >> q;
    vector<string> X, Y;
    while (q--) {
        int type;
        string s;
        cin >> type >> s;
        (type == 1 ? X : Y).push_back(s);
        int alive = 0;
        for (const string& y : Y) {
            bool ok = true;
            for (const string& x : X)
                if (y.compare(0, x.size(), x) == 0) ok = false;
            alive += ok;
        }
        cout << alive << "\n";
    }
}
