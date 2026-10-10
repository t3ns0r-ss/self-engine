#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.5.1. Tasks done one after another from time 0: the sum of the finishing times in the given order,
// and its smallest value (shortest task first, by the adjacent-swap argument).
long long sumOfFinishTimes(const vector<int>& order) {
    long long time = 0, sum = 0;
    for (int d : order) sum += time += d;
    return sum;
}
long long smallestSum(vector<int> a) {
    sort(a.begin(), a.end());
    return sumOfFinishTimes(a);
}
// snippet:end

int main() {
    vector<int> a = {3, 1, 2};
    cout << "durations 3 1 2: input order " << sumOfFinishTimes(a) << ", shortest first " << smallestSum(a) << '\n';
    cout << "durations 5 5 1: input order " << sumOfFinishTimes({5, 5, 1}) << ", shortest first " << smallestSum({5, 5, 1}) << '\n';
    mt19937 rng(1);
    for (int round = 0; round < 300; round++) {
        int n = rng() % 6 + 1;
        vector<int> b(n);
        for (int& x : b) x = rng() % 9 + 1;
        sort(b.begin(), b.end());
        long long best = LLONG_MAX;
        do best = min(best, sumOfFinishTimes(b)); while (next_permutation(b.begin(), b.end()));
        if (best != smallestSum(b)) return 1;
    }
}
