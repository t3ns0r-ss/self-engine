#include <bits/stdc++.h>
using namespace std;

// method: the heap of current gains: take the item with the largest gain, apply it, and put the item back with its next gain.
// gains[i] lists the gains of the successive operations on the item i; ops operations are made.
long long method(const vector<vector<int>>& gains, int ops) {
    priority_queue<tuple<int, int, int>> heap;  // (gain, item, how many operations done)
    for (size_t i = 0; i < gains.size(); i++) heap.push({gains[i][0], (int)i, 0});
    long long total = 0;
    while (ops-- > 0 && !heap.empty()) {
        auto [g, i, done] = heap.top();
        heap.pop();
        total += g;
        if (done + 1 < (int)gains[i].size()) heap.push({gains[i][done + 1], i, done + 1});
    }
    return total;
}
// brute: for every item the number of operations used (its gains are added in order); the largest total.
long long brute(const vector<vector<int>>& gains, int ops) {
    int n = gains.size();
    long long best = LLONG_MIN;
    function<void(int, int, long long)> go = [&](int i, int left, long long total) {
        if (i == n) return void(left == 0 ? best = max(best, total) : best);
        long long sum = 0;
        for (int k = 0; k <= min<int>(left, gains[i].size()); k++) {
            go(i + 1, left - k, total + sum);
            if (k < (int)gains[i].size()) sum += gains[i][k];
        }
    };
    go(0, ops, 0);
    return best;
}
// Huffman: merging two items costs their sum.
long long huffmanMethod(vector<long long> w) {
    priority_queue<long long, vector<long long>, greater<long long>> heap(w.begin(), w.end());
    long long cost = 0;
    while (heap.size() > 1) {
        long long a = heap.top();
        heap.pop();
        long long b = heap.top();
        heap.pop();
        cost += a + b, heap.push(a + b);
    }
    return cost;
}
long long huffmanBrute(vector<long long> w) {
    if (w.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i < w.size(); i++)
        for (size_t j = i + 1; j < w.size(); j++) {
            vector<long long> next;
            for (size_t k = 0; k < w.size(); k++)
                if (k != i && k != j) next.push_back(w[k]);
            next.push_back(w[i] + w[j]);
            best = min(best, w[i] + w[j] + huffmanBrute(next));
        }
    return best;
}
int main() {
    // piles 5, 4, 9 and 2 operations "remove half": the gains of one pile are floor(x / 2) of the successive sizes, and they fall
    vector<int> piles = {5, 4, 9};
    vector<vector<int>> halving;
    long long sum = 0;
    for (int x : piles) {
        halving.push_back({});
        sum += x;
        while (x / 2 > 0) halving.back().push_back(x / 2), x -= x / 2;
    }
    vector<vector<int>> rising = {{0, 10}, {3, 2}};  // the gains of an item do not fall
    cout << "P1 brute=" << sum - brute(halving, 2) << " method=" << sum - method(halving, 2) << "\n";
    cout << "P2 brute=" << huffmanBrute({4, 3, 2, 6}) << " method=" << huffmanMethod({4, 3, 2, 6}) << "\n";
    cout << "N1 brute=" << brute(rising, 2) << " method=" << method(rising, 2) << "\n";
}
