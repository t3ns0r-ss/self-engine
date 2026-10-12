#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 1553, Minimum Number of Days to Eat N Oranges. There are n oranges. Each day you eat one, or, if the number left is
divisible by 2, you eat half of them, or, if it is divisible by 3, you eat two thirds of them. Print the fewest days to eat all.
Input: n (up to 2·10^9).
Output: the number of days.
*/


// snippet:begin
// Theorem 7.2.4: days(n) = 1 + min(n % 2 + days(n / 2), n % 3 + days(n / 3)); every call is on a smaller number, each number is
// computed once, and only about log2(n) · log3(n) numbers can be reached.
long long days(long long n, map<long long, long long>& memo) {
    if (n <= 1) return n;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;
    return memo[n] = 1 + min(n % 2 + days(n / 2, memo), n % 3 + days(n / 3, memo));
}
// snippet:end

int main() {
    long long n;
    cin >> n;
    map<long long, long long> memo;
    cout << days(n, memo) << "\n";
}
