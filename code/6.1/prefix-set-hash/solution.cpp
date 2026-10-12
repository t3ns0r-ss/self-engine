#include <bits/stdc++.h>
using namespace std;

/*
Problem: two sequences A and B of length n and q questions "x y": is the set of values among the first x terms
of A equal to the set of values among the first y terms of B?
Input: n, A, B, q, then q lines x y.
Output: Yes or No for each question.
*/

const long long P = (1LL << 61) - 1;

// snippet:begin
// For every prefix of a, the hash of the SET of its values (a value counts once): the sum of the weights of the
// different values modulo P (Theorem 6.1.6). Both sequences must use the same weight table.
vector<long long> prefixSetHashes(const vector<int>& a, map<int, long long>& weight, mt19937_64& rng) {
    vector<long long> result = {0};
    set<int> seen;
    for (int x : a) {
        if (!weight.count(x)) weight[x] = rng() % P;  // a new value gets a random weight, once
        long long h = result.back();
        if (seen.insert(x).second) h = (h + weight[x]) % P;  // only the first copy of a value counts
        result.push_back(h);
    }
    return result;  // result[i] is the hash of the set of a[0..i)
}
// snippet:end

int main() {
    int n, q;
    cin >> n;
    vector<int> a(n), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    map<int, long long> weight;
    vector<long long> ha = prefixSetHashes(a, weight, rng), hb = prefixSetHashes(b, weight, rng);
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << (ha[x] == hb[y] ? "Yes" : "No") << "\n";
    }
}
