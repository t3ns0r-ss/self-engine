#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    multiset<int> s = {0};
    while (q--) {
        char sign;
        int x;
        cin >> sign >> x;
        if (sign == '+') s.insert(x);
        else if (sign == '-') s.erase(s.find(x));
        else {
            int best = 0;
            for (int y : s) best = max(best, x ^ y);
            cout << best << "\n";
        }
    }
}
