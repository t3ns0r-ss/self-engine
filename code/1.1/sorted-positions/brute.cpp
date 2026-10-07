// place of i = 1 + number of j with a_j < a_i, or a_j == a_i and j < i (Theorem 1.1.4, part 2,
// used here as the definition); the order is read back from the places. O(n^2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> place(n), order(n);
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++)
            if (a[j] < a[i] || (a[j] == a[i] && j < i)) c++;
        place[i] = c;
        order[c] = i;
    }
    for (int k = 0; k < n; k++) cout << order[k] + 1 << (k + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << place[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
