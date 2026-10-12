#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers. Cut the sequence into consecutive pieces so that every piece has at least l numbers and the difference between
the largest and the smallest number in the piece is at most s. Print the fewest pieces, or -1 if there is no such cut.
Input: n, s and l, then the n numbers.
Output: the fewest pieces, or -1.
*/


// snippet:begin
// Theorem 7.3.2 with two moving ends: the starts j of the last piece (j, i] satisfy first <= j <= i - l, where first is the smallest
// start with max - min <= s. One deque for the maximum, one for the minimum, one for the smallest dp over the starts.
int fewestPieces(const vector<int>& a, int s, int l) {
    int n = a.size(), first = 0;
    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    deque<int> mx, mn, best;
    for (int i = 1; i <= n; i++) {
        while (!mx.empty() && a[mx.back()] <= a[i - 1]) mx.pop_back();
        while (!mn.empty() && a[mn.back()] >= a[i - 1]) mn.pop_back();
        mx.push_back(i - 1), mn.push_back(i - 1);
        while (a[mx.front()] - a[mn.front()] > s) {  // move the left end until the piece [first, i) is allowed
            first++;
            if (mx.front() < first) mx.pop_front();
            if (mn.front() < first) mn.pop_front();
        }
        if (i - l >= 0) {  // the start i - l becomes allowed
            while (!best.empty() && dp[best.back()] >= dp[i - l]) best.pop_back();
            best.push_back(i - l);
        }
        while (!best.empty() && best.front() < first) best.pop_front();
        if (!best.empty() && dp[best.front()] < INF) dp[i] = dp[best.front()] + 1;
    }
    return dp[n] < INF ? dp[n] : -1;
}
// snippet:end

int main() {
    int n, s, l;
    cin >> n >> s >> l;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << fewestPieces(a, s, l) << "\n";
}
