#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    long long t;
    cin >> s >> t;
    vector<int> nums(26);
    for (int& x : nums) cin >> x;
    vector<long long> count(26, 0);
    for (char ch : s) count[ch - 'a']++;
    for (long long step = 0; step < t; step++) {  // t is small in the tests: count the letters after each transformation
        vector<long long> next(26, 0);
        for (int i = 0; i < 26; i++)
            for (int d = 1; d <= nums[i]; d++) next[(i + d) % 26] = (next[(i + d) % 26] + count[i]) % 1000000007;
        count = next;
    }
    long long total = 0;
    for (long long c : count) total = (total + c) % 1000000007;
    cout << total << "\n";
}
