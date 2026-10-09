// Card example unit (PLAN.md Section 8.6) for the card "Sliding window extremes": the numbers behind its
// inline examples. "P<k>" lines are positive examples, "N<k>" negative ones.
#include <bits/stdc++.h>
using namespace std;

// The card's method: the deque of Theorem 1.6.3 gives the maximum of every window of length k.
vector<int> deque_max(const vector<int>& a, int k) {
    deque<int> dq;
    vector<int> out;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) out.push_back(a[dq.front()]);
    }
    return out;
}

string join(const vector<int>& v) {
    string s;
    for (int i = 0; i < (int)v.size(); i++) s += (i ? "," : "") + to_string(v[i]);
    return s;
}

int main() {
    // P1: maxima of the windows of length 3 of (5, 1, 3, 2, 6, 4).
    vector<int> a = {5, 1, 3, 2, 6, 4}, brute;
    for (int l = 0; l + 3 <= 6; l++) brute.push_back(*max_element(a.begin() + l, a.begin() + l + 3));
    cout << "P1 brute=" << join(brute) << " method=" << join(deque_max(a, 3)) << '\n';

    // N1: the MEDIAN of every window of length 3 of (1, 5, 2, 4); the deque only knows the maximum.
    vector<int> b = {1, 5, 2, 4}, med;
    for (int l = 0; l + 3 <= 4; l++) {
        vector<int> w(b.begin() + l, b.begin() + l + 3);
        sort(w.begin(), w.end());
        med.push_back(w[1]);
    }
    cout << "N1 brute=" << join(med) << " method=" << join(deque_max(b, 3)) << '\n';

    // N2: two queries on (1, 7, 2, 3, 4): the maximum of a[2..4], then of a[0..4]. The deque built for the
    // window [2, 4] has already dropped position 1, so it answers both queries with the same front.
    vector<int> c = {1, 7, 2, 3, 4};
    vector<int> truth = {*max_element(c.begin() + 2, c.begin() + 5), *max_element(c.begin(), c.begin() + 5)};
    int front = deque_max(c, 3).back();
    cout << "N2 brute=" << join(truth) << " method=" << join({front, front}) << '\n';
}
