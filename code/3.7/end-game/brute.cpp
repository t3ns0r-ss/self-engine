// Brute force: plain minimax recursion over the remaining segment, returning (mover's total, other's total).
#include <bits/stdc++.h>
using namespace std;

vector<long long> a;

pair<long long, long long> play(int l, int r) {
    if (l > r) return {0, 0};
    auto left = play(l + 1, r), right = play(l, r - 1);  // the opponent moves next
    long long takeLeft = a[l] + left.second, takeRight = a[r] + right.second;
    if (takeLeft >= takeRight) return {takeLeft, left.first};
    return {takeRight, right.first};
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    for (auto& x : a) cin >> x;
    cout << play(0, n - 1).first << "\n";
}
