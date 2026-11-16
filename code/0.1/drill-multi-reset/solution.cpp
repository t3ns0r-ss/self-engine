/*
Drill (about 4 minutes). t test cases. In each, n integers with 1 <= a_i <= n. Print how many different values occur.
The trap: a counting array that is made once and not cleared between tests keeps the values of the earlier test.
Input: t, then for each test n and a_1..a_n. The sum of n over all tests is at most 2*10^5.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The counting array is created inside the loop, with the size of this test: nothing can be left over, and
// the work per test is n, not the largest n.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<char> seen(n + 1, 0);
        int distinct = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (!seen[a]) {
                seen[a] = 1;
                distinct++;
            }
        }
        cout << distinct << "\n";
    }
}
// snippet:end
