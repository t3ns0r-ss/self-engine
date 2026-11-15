// Brute force: every set partition, built by putting each item into an existing group or a new one.
#include <bits/stdc++.h>
using namespace std;

int n;
long long cap, best = -1;
vector<long long> w, load;

void place(int i) {
    if (i == n) {
        long long cost = 0;
        for (long long l : load) cost += l * l;
        best = max(best, cost);
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
    place(0);
    cout << best << "\n";
}
