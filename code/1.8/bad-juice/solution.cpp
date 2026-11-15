#include <bits/stdc++.h>
using namespace std;

/*
Problem: n bottles, exactly one is bad. Call as few friends as possible, give each friend some bottles (all questions
are printed before any reply), then learn which friends got sick and name the bad bottle.
Input: n. Output: m, then m lines "k b_1 .. b_k" (friend j drinks the k listed bottles), then the bottle number
after the string of m digits (1 = sick) is read.
*/

// snippet:begin
// Friend j drinks bottle i when bit j of i - 1 is 1, so the sick friends spell the number of the bad bottle in binary.
// m is the smallest number with 2^m >= n: one yes/no reply per friend cannot tell more than 2^m bottles apart.
int bottleOfFriends(int n) {
    int m = 0;
    while ((1 << m) < n) m++;
    cout << m << "\n";
    for (int j = 0; j < m; j++) {
        vector<int> drinks;
        for (int i = 1; i <= n; i++)
            if ((i - 1) >> j & 1) drinks.push_back(i);
        cout << drinks.size();
        for (int b : drinks) cout << " " << b;
        cout << "\n";
    }
    cout << flush;                 // all the lines are sent together, once
    string sick;
    cin >> sick;
    int bad = 0;
    for (int j = 0; j < m; j++)
        if (sick[j] == '1') bad |= 1 << j;
    return bad + 1;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    int bad = bottleOfFriends(n);
    cout << bad << endl;
    return 0;
}
