#include <bits/stdc++.h>
using namespace std;

int cyclesOf(const vector<int>& p) {
    int n = p.size(), c = 0;
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++)
        if (!seen[i]) {
            c++;
            for (int j = i; !seen[j]; j = p[j] - 1) seen[j] = true;
        }
    return c;
}
int bfsSwaps(vector<int> p) {  // the least number of swaps, by a search over all permutations
    int n = p.size();
    vector<int> target(n);
    iota(target.begin(), target.end(), 1);
    map<vector<int>, int> dist;
    queue<vector<int>> q;
    dist[p] = 0, q.push(p);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == target) return dist[cur];
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                auto next = cur;
                swap(next[i], next[j]);
                if (!dist.count(next)) dist[next] = dist[cur] + 1, q.push(next);
            }
    }
    return -1;
}
int bfsFlips(vector<int> p) {  // the least number of prefix reversals
    int n = p.size();
    vector<int> target(n);
    iota(target.begin(), target.end(), 1);
    map<vector<int>, int> dist;
    queue<vector<int>> q;
    dist[p] = 0, q.push(p);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == target) return dist[cur];
        for (int k = 1; k <= n; k++) {
            auto next = cur;
            reverse(next.begin(), next.begin() + k);
            if (!dist.count(next)) dist[next] = dist[cur] + 1, q.push(next);
        }
    }
    return -1;
}
// method: for k = n down to 2, bring the value k to the front (if it is not there) and then to the position k.
vector<int> pancakeFlips(vector<int> p) {
    vector<int> flips;
    for (int k = p.size(); k >= 2; k--) {
        int pos = max_element(p.begin(), p.begin() + k) - p.begin();
        if (pos + 1 == k) continue;
        if (pos != 0) flips.push_back(pos + 1), reverse(p.begin(), p.begin() + pos + 1);
        flips.push_back(k);
        reverse(p.begin(), p.begin() + k);
    }
    return flips;
}
int main() {
    vector<int> a = {2, 3, 1, 5, 4};
    cout << "P1 brute=" << bfsSwaps(a) << " method=" << a.size() - cyclesOf(a) << "\n";
    vector<int> b = {3, 2, 4, 1};
    int limit = 2 * b.size() - 3;  // the greedy uses at most 2 flips for each of the n - 1 values, and none for the last
    cout << "P2 brute=" << (bfsFlips(b) <= limit ? "yes" : "no") << " method=" << ((int)pancakeFlips(b).size() <= 2 * (int)b.size() ? "yes" : "no") << "\n";
    cout << "N1 brute=" << bfsFlips(b) << " method=" << pancakeFlips(b).size() << "\n";
    // N2: the least number of swaps of two NEIGHBOURING elements for [3, 2, 1] (the number of inversions), against n - c
    vector<int> c = {3, 2, 1};
    int inversions = 0;
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 3; j++) inversions += c[i] > c[j];
    cout << "N2 brute=" << inversions << " method=" << c.size() - cyclesOf(c) << "\n";
}
