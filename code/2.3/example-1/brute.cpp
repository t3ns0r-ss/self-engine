#include <bits/stdc++.h>
using namespace std;

long long X, Y, cnt = 0;

void go(long long i, long long j) {  // every sequence of moves, recursively
    if (i == X && j == Y) {
        cnt++;
        return;
    }
    if (i > X || j > Y) return;
    go(i + 1, j + 2);
    go(i + 2, j + 1);
}

int main() {
    cin >> X >> Y;
    go(0, 0);
    cout << cnt % 1000000007 << "\n";
}
