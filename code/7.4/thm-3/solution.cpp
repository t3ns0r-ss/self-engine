#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.4.3 (a). One operation halves one number; the gains x/2, x/4, ... of a number fall, so the best operation is always on the
// current largest. The fewest operations that remove at least half of the sum.
int halvingsToHalveSum(const vector<int>& nums) {
    priority_queue<double> heap(nums.begin(), nums.end());
    double need = accumulate(nums.begin(), nums.end(), 0.0) / 2, removed = 0;
    int operations = 0;
    while (removed < need) {
        double largest = heap.top();
        heap.pop();
        removed += largest / 2, heap.push(largest / 2), operations++;
    }
    return operations;
}
// Theorem 7.4.3 (b). Merging two items costs their sum; the cheapest way to merge all of them merges the two smallest again and again.
long long mergeCost(const vector<long long>& weights) {
    priority_queue<long long, vector<long long>, greater<long long>> heap(weights.begin(), weights.end());
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
// snippet:end

int bruteHalvings(const vector<int>& nums) {  // iterative deepening over every sequence of choices
    int n = nums.size();
    double need = accumulate(nums.begin(), nums.end(), 0.0) / 2;
    for (int len = 0;; len++) {
        function<bool(vector<double>, int, double)> go = [&](vector<double> v, int left, double removed) {
            if (removed >= need) return true;
            if (left == 0) return false;
            for (int i = 0; i < n; i++) {
                double half = v[i] / 2;
                vector<double> w = v;
                w[i] = half;
                if (go(w, left - 1, removed + half)) return true;
            }
            return false;
        };
        if (go(vector<double>(nums.begin(), nums.end()), len, 0)) return len;
    }
}
long long bruteMerge(vector<long long> w) {  // every pair, recursively
    if (w.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i < w.size(); i++)
        for (size_t j = i + 1; j < w.size(); j++) {
            vector<long long> next;
            for (size_t k = 0; k < w.size(); k++)
                if (k != i && k != j) next.push_back(w[k]);
            next.push_back(w[i] + w[j]);
            best = min(best, w[i] + w[j] + bruteMerge(next));
        }
    return best;
}

int main() {
    cout << "halvings 1: " << halvingsToHalveSum({5, 19, 8, 1}) << "\n";
    cout << "halvings 2: " << halvingsToHalveSum({3, 8, 20}) << "\n";
    cout << "merge cost 1: " << mergeCost({4, 3, 2, 6}) << "\n";
    cout << "merge cost 2: " << mergeCost({5}) << "\n";
    // Check (not printed): 1500 random cases of up to 4 numbers for the halvings and 3000 of up to 6 weights for the merges.
    mt19937 rng(23);
    for (int it = 0; it < 1500; it++) {
        int n = rng() % 4 + 1;
        vector<int> v(n);
        for (int& x : v) x = rng() % 12 + 1;
        if (halvingsToHalveSum(v) != bruteHalvings(v)) return 1;
    }
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 6 + 1;
        vector<long long> w(n);
        for (auto& x : w) x = rng() % 9 + 1;
        if (mergeCost(w) != bruteMerge(w)) return 1;
    }
}
