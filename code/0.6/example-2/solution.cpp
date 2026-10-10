/*
Problem: AtCoder ABC 237 D LR insertion. Start from A = (0); for i = 1..N insert i immediately left
(L) or right (R) of i - 1. Print the final sequence.
Input: N (1 <= N <= 5*10^5), then a string S of N letters L and R.
Output: the final sequence.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The final sequence of "LR insertion". Process i = N down to 1: when i-1 is placed, i (and everything
// inserted after it) is already a block in the deque. i-1 goes to its right if S_i is L, to its left if R.
vector<int> lrInsertion(int n, const string& s) {
    deque<int> d = {n};
    for (int i = n; i >= 1; i--) {
        if (s[i - 1] == 'L') d.push_back(i - 1);
        else d.push_front(i - 1);
    }
    return vector<int>(d.begin(), d.end());
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    vector<int> r = lrInsertion(n, s);
    for (int k = 0; k <= n; k++) cout << r[k] << (k < n ? ' ' : '\n');
}
