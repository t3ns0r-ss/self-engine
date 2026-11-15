#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<int> a(n), all;
    for (int& x : a) cin >> x;
    for (long long t = 0; t < T; t++) all.insert(all.end(), a.begin(), a.end());
    vector<int> best(all.size(), 1);
    int answer = 0;
    for (size_t i = 0; i < all.size(); i++) {
        for (size_t j = 0; j < i; j++)
            if (all[j] <= all[i]) best[i] = max(best[i], best[j] + 1);
        answer = max(answer, best[i]);
    }
    cout << answer << "\n";
}
