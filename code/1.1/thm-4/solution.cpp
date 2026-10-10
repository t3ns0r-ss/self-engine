#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.4. Sort (value, index) pairs. order[k] = the original index of the k-th smallest value,
// place[i] = the place of a_i; equal values keep the order of their indices.
void sortedPositions(const vector<int>& a, vector<int>& order, vector<int>& place) {
    int n = a.size();
    vector<pair<int, int>> v(n);  // the index travels with its value
    for (int i = 0; i < n; i++) v[i] = {a[i], i};
    sort(v.begin(), v.end());
    order.assign(n, 0), place.assign(n, 0);
    for (int k = 0; k < n; k++) order[k] = v[k].second, place[v[k].second] = k;
}
// snippet:end

int main() {
    vector<int> order, place;
    sortedPositions({50, 10, 50, 7}, order, place);
    cout << "50 10 50 7: sorted order of the indices:";
    for (int x : order) cout << ' ' << x;
    cout << "\n50 10 50 7: place of each element:";
    for (int x : place) cout << ' ' << x;
    cout << '\n';
    mt19937 rng(10);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 5;
        sortedPositions(a, order, place);
        for (int i = 0; i < n; i++) {
            int smaller = 0;  // the number of j with a_j < a_i, or a_j = a_i and j < i
            for (int j = 0; j < n; j++) smaller += a[j] < a[i] || (a[j] == a[i] && j < i);
            if (place[i] != smaller || order[place[i]] != i) return 1;
        }
    }
}
