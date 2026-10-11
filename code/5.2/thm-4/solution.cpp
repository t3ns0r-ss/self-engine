#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.2.4. The number of pairs i < j with a[i] > a[j]; equal values are not counted.
long long countInversions(const vector<int>& a) {
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int m = sorted.size();
    vector<int> tree(m + 1, 0);  // tree over ranks 1..m: how many earlier elements have each rank
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
    auto show = [](vector<int> a) {
        cout << "a =";
        for (int x : a) cout << ' ' << x;
        cout << ": " << countInversions(a) << " inversions\n";
    };
    show({2, 4, 1, 3, 5});
    show({3, 3, 3});
    show({5, 4, 3, 2, 1});
    // Check against: counting the pairs one by one, on every array of length 1..6 over {1, 2, 3}.
    for (int n = 1; n <= 6; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 3;
        for (int code = 0; code < total; code++) {
            vector<int> a(n);
            for (int i = 0, c = code; i < n; i++, c /= 3) a[i] = c % 3 + 1;
            long long brute = 0;
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++) brute += a[i] > a[j];
            if (countInversions(a) != brute) return 1;
        }
    }
}
