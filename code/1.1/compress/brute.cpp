// rank of a_i = number of j with a_j < a_i such that a_j does not occur at an earlier index
// (each distinct smaller value counted once). O(n^3).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto firstOccurrence = [&](int j) {
        for (int t = 0; t < j; t++)
            if (a[t] == a[j]) return false;
        return true;
    };
    int distinct = 0;
    for (int j = 0; j < n; j++) distinct += firstOccurrence(j);
    cout << distinct << "\n";
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++)
            if (a[j] < a[i] && firstOccurrence(j)) c++;
        cout << c << (i + 1 < n ? ' ' : '\n');
    }
}
