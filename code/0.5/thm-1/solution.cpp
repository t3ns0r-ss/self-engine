#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.1. Exhaustive search over all pairs i < j: how many pairs add up to target.
// The number of candidates is n(n-1)/2 pairs or n(n-1)(n-2)/6 triples.
int countPairs(const vector<int>& a, int target) {
    int count = 0;
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = i + 1; j < (int)a.size(); j++)
            if (a[i] + a[j] == target) count++;
    return count;
}
long long pairCandidates(long long n) { return n * (n - 1) / 2; }
long long tripleCandidates(long long n) { return n * (n - 1) * (n - 2) / 6; }
// snippet:end

int main() {
    cout << "pairs adding up to 6 in 1 2 3 4 5: " << countPairs({1, 2, 3, 4, 5}, 6) << '\n';
    cout << "pairs among 10000 items: " << pairCandidates(10000) << '\n';
    cout << "triples among 800 items: " << tripleCandidates(800) << '\n';
    for (int n = 0; n <= 12; n++) {
        long long pairs = 0, triples = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                pairs++;
                for (int k = j + 1; k < n; k++) triples++;
            }
        if (pairs != pairCandidates(n) || triples != tripleCandidates(n)) return 1;
    }
}
