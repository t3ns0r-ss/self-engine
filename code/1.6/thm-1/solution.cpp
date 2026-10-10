#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.1. next[i]: next greater element of i; prev[i]: previous greater-or-equal element. -1 = none.
void scan(const vector<int>& a, vector<int>& next, vector<int>& prev) {
    int n = a.size();
    next.assign(n, -1), prev.assign(n, -1);
    vector<int> st;  // positions; values never increase from bottom to top
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) {
            next[st.back()] = i;
            st.pop_back();
        }
        if (!st.empty()) prev[i] = st.back();
        st.push_back(i);
    }
}
// snippet:end

void show(const vector<int>& a) {
    vector<int> next, prev;
    scan(a, next, prev);
    cout << "a =";
    for (int x : a) cout << ' ' << x;
    cout << "\nnext greater:";
    for (int x : next) cout << ' ' << x;
    cout << "\nprevious greater-or-equal:";
    for (int x : prev) cout << ' ' << x;
    cout << '\n';
}

int main() {
    show({2, 1, 4, 3, 5});
    show({3, 3, 1, 2});
    vector<int> b(5), next, prev;  // every array of length 5 over {1, 2, 3} against the definitions
    for (int code = 0; code < 243; code++) {
        for (int i = 0, c = code; i < 5; i++, c /= 3) b[i] = c % 3 + 1;
        scan(b, next, prev);
        for (int i = 0; i < 5; i++) {
            int nx = -1, pv = -1;
            for (int j = 4; j > i; j--) if (b[j] > b[i]) nx = j;
            for (int j = 0; j < i; j++) if (b[j] >= b[i]) pv = j;
            if (nx != next[i] || pv != prev[i]) return 1;
        }
    }
}
