#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 992, Subarrays with K Different Integers. Given an array of n integers (n up to 2·10^4) and a number k, count the
contiguous subarrays that contain exactly k different values.
Input: n and k, then the n values.
*/

// snippet:begin
// "Exactly k" is not monotone in the window, but "at most k" is: shrinking a window never adds a new value. So count the subarrays with
// at most k different values with a sliding window, and subtract the count for k - 1.
long long atMost(const vector<int>& a, int k) {
    map<int, int> inWindow;
    long long total = 0;
    for (int left = 0, right = 0; right < (int)a.size(); right++) {
        inWindow[a[right]]++;
        while ((int)inWindow.size() > k) {
            if (--inWindow[a[left]] == 0) inWindow.erase(a[left]);
            left++;
        }
        total += right - left + 1;  // the windows ending at right that start at left ... right
    }
    return total;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << atMost(a, k) - atMost(a, k - 1) << "\n";
}
