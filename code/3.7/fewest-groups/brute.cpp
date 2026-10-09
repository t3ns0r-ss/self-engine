// Brute force: put each item into one of the existing groups or a new one, by recursion over all set partitions.
#include <bits/stdc++.h>
using namespace std;

int n, best;
long long cap;
vector<long long> w, load;

void place(int i) {
    if ((int)load.size() >= best) return;
    if (i == n) {
        best = load.size();
        return;
    }
    for (size_t g = 0; g < load.size(); g++)  // an index, since deeper calls may grow the vector
        if (load[g] + w[i] <= cap) {
            load[g] += w[i];
            place(i + 1);
            load[g] -= w[i];
        }
    load.push_back(w[i]);
    place(i + 1);
    load.pop_back();
}

int main() {
    cin >> n >> cap;
    w.resize(n);
    for (auto& x : w) cin >> x;
    best = n + 1;
    place(0);
    cout << best << "\n";
}
