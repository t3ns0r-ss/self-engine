#include <bits/stdc++.h>
using namespace std;
void scan(const vector<int>& a, vector<int>& nxt, vector<int>& prv, bool show) {  // nxt: next greater, prv: previous greater-or-equal, -1 = none
    vector<int> st;
    nxt.assign(a.size(), -1), prv.assign(a.size(), -1);
    for (int i = 0; i < (int)a.size(); i++) {
        if (show) cout << "step " << i << " (a=" << a[i] << ") popped:";
        while (!st.empty() && a[st.back()] < a[i]) { if (show) cout << ' ' << st.back(); nxt[st.back()] = i; st.pop_back(); }
        if (!st.empty()) prv[i] = st.back();
        st.push_back(i);
        if (show) { cout << " | stack values:"; for (int j : st) cout << ' ' << a[j]; cout << '\n'; }
    }
}
int main() {
    vector<int> a = {2, 1, 4, 3, 5}, nxt, prv, b(5), n2, p2; int bad = 0;
    scan(a, nxt, prv, true);
    cout << "next greater:"; for (int x : nxt) cout << ' ' << x; cout << '\n';
    cout << "previous greater-or-equal:"; for (int x : prv) cout << ' ' << x; cout << '\n';
    for (int code = 0; code < 243; code++) {  // every array of length 5 over {1, 2, 3}
        for (int i = 0, c = code; i < 5; i++, c /= 3) b[i] = c % 3 + 1;
        scan(b, n2, p2, false);
        for (int i = 0; i < 5; i++) {
            int nx = -1, pv = -1;
            for (int j = 4; j > i; j--) if (b[j] > b[i]) nx = j;   // the smallest such j wins
            for (int j = 0; j < i; j++) if (b[j] >= b[i]) pv = j;  // the largest such j wins
            bad += nx != n2[i] || pv != p2[i];
        }
    }
    cout << "all 243 arrays of length 5 over {1,2,3}: scan equals brute force: " << (bad ? "no" : "yes") << '\n';
}
