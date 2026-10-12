#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.1.6. The hash of a set (or multiset) of values: add a random weight for every element.
// weight[v] are fixed random numbers modulo p, one per possible value v; the order of the elements does not matter.
long long setHash(const vector<int>& values, const vector<long long>& weight, long long p) {
    long long h = 0;
    for (int v : values) h = (h + weight[v]) % p;
    return h;
}
// How many weight tables (each weight in 0..p-1, three values) give two multisets the same hash?
int badTables(const vector<int>& a, const vector<int>& b, long long p) {
    int bad = 0;
    for (long long w0 = 0; w0 < p; w0++)
        for (long long w1 = 0; w1 < p; w1++)
            for (long long w2 = 0; w2 < p; w2++) {
                vector<long long> weight = {w0, w1, w2};
                if (setHash(a, weight, p) == setHash(b, weight, p)) bad++;
            }
    return bad;
}
// snippet:end

int main() {
    // The values are 0, 1, 2. With p = 5 there are 125 weight tables.
    cout << "{0,1} vs {1,0}: " << badTables({0, 1}, {1, 0}, 5) << " of 125\n";
    cout << "{0,1} vs {0,2}: " << badTables({0, 1}, {0, 2}, 5) << " of 125\n";
    cout << "{0,0} vs {1,1}: " << badTables({0, 0}, {1, 1}, 5) << " of 125\n";
    cout << "{0,1,2} vs {0,0,0}: " << badTables({0, 1, 2}, {0, 0, 0}, 5) << " of 125\n";
    // Check (not printed): for p in {3, 5, 7} and all pairs of multisets of size <= 3 over {0, 1, 2}
    // that differ as multisets, exactly 1/p of the tables collide when some count differs by an amount that is not a multiple of p.
    for (long long p : {3LL, 5LL, 7LL}) {
        vector<vector<int>> all;
        for (int len = 0; len <= 3; len++) {
            vector<int> cur(len, 0);
            while (true) {
                all.push_back(cur);
                int i = len - 1;
                while (i >= 0 && cur[i] == 2) cur[i--] = 0;
                if (i < 0) break;
                cur[i]++;
            }
        }
        for (auto& a : all)
            for (auto& b : all) {
                bool someCountDiffers = false;  // the proof needs a count difference that is not a multiple of p
                for (int v = 0; v < 3; v++)
                    if ((count(a.begin(), a.end(), v) - count(b.begin(), b.end(), v)) % p != 0) someCountDiffers = true;
                if (!someCountDiffers) continue;
                long long total = p * p * p;
                if (badTables(a, b, p) * p != total) return 1;
            }
    }
}
