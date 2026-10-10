#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: sequences of length 3 over {1, 2}. Brute: three nested loops. Method: recursion.
    int brute = 0;
    for (int a = 1; a <= 2; a++) for (int b = 1; b <= 2; b++) for (int c = 1; c <= 2; c++) brute++;
    function<int(int)> rec = [&](int pos) { return pos == 3 ? 1 : rec(pos + 1) + rec(pos + 1); };
    cout << "P1 brute=" << brute << " method=" << rec(0) << '\n';
    // P2: non-decreasing sequences of length 2 over 1..3. Brute: two loops. Method: recursion with "at least the previous".
    brute = 0;
    for (int a = 1; a <= 3; a++) for (int b = 1; b <= 3; b++) brute += a <= b;
    function<int(int, int)> rec2 = [&](int pos, int prev) {
        if (pos == 2) return 1;
        int total = 0;
        for (int v = prev; v <= 3; v++) total += rec2(pos + 1, v);
        return total;
    };
    cout << "P2 brute=" << brute << " method=" << rec2(0, 1) << '\n';
    // N1: strictly increasing sequences of length 2 over 1..4. Brute: the valid ones. Method: the 4^2 sequences listed.
    brute = 0;
    for (int a = 1; a <= 4; a++) for (int b = a + 1; b <= 4; b++) brute++;
    cout << "N1 brute=" << brute << " method=" << 4 * 4 << '\n';
    // N2: sequences of length 2 over 1..3 with |c1 - c0| <= 1, where the recursion forgets the condition.
    brute = 0;
    for (int a = 1; a <= 3; a++) for (int b = 1; b <= 3; b++) brute += abs(a - b) <= 1;
    cout << "N2 brute=" << brute << " method=" << 3 * 3 << '\n';
}
