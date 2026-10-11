#include <bits/stdc++.h>
using namespace std;

/*
Problem: the number of pairs i < j with a_i > a_j (inversions).
Input: n, then the n numbers (|a_i| <= 10^9).
Output: the number of inversions.
*/

// snippet:begin
// The number of pairs i < j with a[i] > a[j]; equal values are not counted. Values become ranks first.
long long countInversions(const vector<int>& a) {
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int m = sorted.size();
    vector<int> tree(m + 1, 0);  // how many earlier elements have each rank
    long long inversions = 0;    // up to n(n-1)/2, about 2*10^10
    for (int j = 0; j < (int)a.size(); j++) {
        int rank = lower_bound(sorted.begin(), sorted.end(), a[j]) - sorted.begin() + 1;
        int notGreater = 0;  // earlier elements with rank <= rank
        for (int i = rank; i > 0; i -= i & -i) notGreater += tree[i];
        inversions += j - notGreater;  // the other earlier elements are greater
        for (int i = rank; i <= m; i += i & -i) tree[i]++;
    }
    return inversions;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << countInversions(a) << "\n";
}
