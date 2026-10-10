#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.3. Maximum of every window of k consecutive elements.
vector<int> windowMax(const vector<int>& a, int k) {
    deque<int> dq;  // positions; values strictly decrease from front to back
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();  // left the window [i - k + 1, i]
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
// snippet:end

int main() {
    for (auto [a, k] : {pair{vector<int>{1, 3, -1, -3, 5}, 3}, pair{vector<int>{4, 4, 2, 1}, 2}}) {
        cout << "a =";
        for (int x : a) cout << ' ' << x;
        cout << ", k = " << k << ": maxima";
        for (int x : windowMax(a, k)) cout << ' ' << x;
        cout << '\n';
    }
    vector<int> b(6);  // every array of length 6 over {1, 2, 3}, every k
    for (int code = 0; code < 729; code++) {
        for (int i = 0, c = code; i < 6; i++, c /= 3) b[i] = c % 3 + 1;
        for (int k = 1; k <= 6; k++) {
            vector<int> got = windowMax(b, k);
            for (int l = 0; l + k <= 6; l++)
                if (got[l] != *max_element(b.begin() + l, b.begin() + l + k)) return 1;
        }
    }
}
