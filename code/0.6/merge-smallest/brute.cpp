// Finds the two smallest piles by scanning a vector at every step.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> v(n);
    for (auto& x : v) cin >> x;
    long long cost = 0;
    while (v.size() > 1) {
        long long merged = 0;
        for (int rep = 0; rep < 2; rep++) {
            size_t k = 0;
            for (size_t i = 1; i < v.size(); i++)
                if (v[i] < v[k]) k = i;
            merged += v[k];
            v.erase(v.begin() + k);
        }
        cost += merged;
        v.push_back(merged);
    }
    cout << cost << "\n";
}
