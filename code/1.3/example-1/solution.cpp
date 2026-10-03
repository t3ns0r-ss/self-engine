/*
Problem: CSES 1141 Playlist. Longest run of consecutive songs with no song repeated.
Input: n, then n song ids (1 <= n <= 2*10^5, ids up to 10^9).
Output: the length of the longest such run.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> k(n);
    for (auto& x : k) cin >> x;

    map<int, int> cnt;  // song id -> occurrences in the window k[l..r]
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        cnt[k[r]]++;
        while (cnt[k[r]] > 1) {  // k[r] repeats: shrink until its earlier copy leaves
            cnt[k[l]]--;
            l++;
        }
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
