#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 1425, Constrained Subsequence Sum. An integer array nums (up to 10^5 numbers, possibly negative) and an integer k.
Print the largest sum of a non-empty subsequence in which any two consecutive chosen elements nums[i], nums[j] with i < j satisfy
j - i <= k.
Input: n and k, then the n numbers.
*/


// snippet:begin
// Theorem 7.3.2: dp[i] = nums[i] + max(0, max dp[j] over i - k <= j < i); the answer is the largest dp. The deque keeps the window's
// indices with decreasing dp.
long long constrainedSum(const vector<long long>& nums, int k) {
    vector<long long> dp(nums.size());
    deque<int> window;
    long long best = LLONG_MIN;
    for (int i = 0; i < (int)nums.size(); i++) {
        while (!window.empty() && window.front() < i - k) window.pop_front();
        dp[i] = nums[i] + (window.empty() ? 0 : max(0LL, dp[window.front()]));
        while (!window.empty() && dp[window.back()] <= dp[i]) window.pop_back();
        window.push_back(i);
        best = max(best, dp[i]);
    }
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> nums(n);
    for (long long& x : nums) cin >> x;
    cout << constrainedSum(nums, k) << "\n";
}
