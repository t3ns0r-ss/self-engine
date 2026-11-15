#include <bits/stdc++.h>
using namespace std;

/*
Problem: the judge holds n >= 3 whole numbers a_1 .. a_n, each between 0 and 10^9 (so a reply is never -1).
Input: n. A question "? i j" (i != j) is answered with a_i + a_j. At most n questions are allowed.
Output: "! a_1 ... a_n".
*/

// snippet:begin
// Asks for a_i + a_j. The reply can be 2 * 10^9, so it is kept in a long long. endl flushes the question.
long long pairSum(int i, int j) {
    cout << "? " << i << " " << j << endl;
    long long reply;
    cin >> reply;
    if (reply == -1) exit(0);
    return reply;
}

// Three sums give the first three numbers; one more sum with a_1 gives each further number: n questions in all.
vector<long long> restore(int n) {
    vector<long long> a(n + 1);
    long long s12 = pairSum(1, 2), s13 = pairSum(1, 3), s23 = pairSum(2, 3);
    a[1] = (s12 + s13 - s23) / 2;  // s12 + s13 - s23 = 2 * a_1, which is even, so the division is exact
    a[2] = s12 - a[1];
    a[3] = s13 - a[1];
    for (int i = 4; i <= n; i++) a[i] = pairSum(1, i) - a[1];
    return a;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a = restore(n);
    cout << "!";
    for (int i = 1; i <= n; i++) cout << " " << a[i];
    cout << endl;
    return 0;
}
