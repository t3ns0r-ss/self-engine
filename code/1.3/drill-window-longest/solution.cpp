/*
Drill (about 5 minutes). All a_i are positive. Print the length of the longest block of consecutive elements whose sum
is at most K (0 if even one element is above K).
Input: n K, then a_1..a_n (1 <= a_i <= 10^9, 1 <= K <= 10^15), n <= 2*10^5.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The right end moves forward once; the left end moves forward while the block is too heavy.
// Positive values make "too heavy" stay true until an element leaves, so the left end never goes back.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long sum = 0;
    int left = 0, best = 0;
    for (int right = 0; right < n; right++) {
        sum += a[right];
        while (sum > K) sum -= a[left++];
        best = max(best, right - left + 1);
    }
    cout << best << "\n";
}
// snippet:end
