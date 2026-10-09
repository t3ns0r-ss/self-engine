#include <bits/stdc++.h>
using namespace std;
vector<int> window_max(const vector<int>& a, int k, bool show, bool& ok) {  // Theorem 1.6.3; ok = deque always strictly decreasing
    deque<int> dq; vector<int> out;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        for (int j = 1; j < (int)dq.size(); j++) ok &= a[dq[j - 1]] > a[dq[j]];
        if (i >= k - 1) out.push_back(a[dq.front()]);
        if (!show) continue;
        cout << "i=" << i << " deque positions:"; for (int j : dq) cout << ' ' << j;
        cout << " | values:"; for (int j : dq) cout << ' ' << a[j];
        cout << " | window max: " << (i >= k - 1 ? to_string(out.back()) : "none") << '\n';
    }
    return out;
}
int main() {
    vector<int> a = {1, 3, -1, -3, 5}, b(6); bool ok = true; int bad = 0;
    vector<int> m = window_max(a, 3, true, ok);
    cout << "maxima:"; for (int x : m) cout << ' ' << x; cout << '\n';
    for (int code = 0; code < 729; code++) {  // every array of length 6 over {1, 2, 3}, every k
        for (int i = 0, c = code; i < 6; i++, c /= 3) b[i] = c % 3 + 1;
        for (int k = 1; k <= 6; k++) {
            vector<int> got = window_max(b, k, false, ok);
            for (int l = 0; l + k <= 6; l++) bad += got[l] != *max_element(b.begin() + l, b.begin() + l + k);
        }
    }
    cout << "all 729 arrays of length 6 over {1,2,3}, every k: deque equals brute force and decreases strictly: " << (bad == 0 && ok ? "yes" : "no") << '\n';
}
