#include <bits/stdc++.h>
using namespace std;

/*
Problem: a game on the numbers 1 .. 2n + 1. We name an unused number, then the judge names an unused number, and so
on; whoever cannot name a number loses. We move first and must win against any judge.
Input: n, then after each of our numbers the judge's number (0 when the judge has none left: we won).
Output: our numbers, one per line.
*/

// snippet:begin
// Name the middle number first. After that, answer every judge number x with its partner 2n + 2 - x:
// the unused numbers always come in pairs, so a partner is always free.
void play(int n) {
    cout << n + 1 << endl;                  // endl flushes: the judge waits for each number
    while (true) {
        int x;
        cin >> x;
        if (x == 0 || x == -1) return;      // 0: the judge cannot move, we won. -1: a refused move: quit
        cout << 2 * n + 2 - x << endl;
    }
}
// snippet:end

int main() {
    int n;
    cin >> n;
    play(n);
    return 0;
}
