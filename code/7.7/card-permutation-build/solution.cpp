#include <bits/stdc++.h>
using namespace std;

// brute: a search over all permutations of 1 ... n for those with exactly k distinct neighbour differences.
int distinctDifferences(const vector<int>& p) {
    set<int> d;
    for (size_t i = 0; i + 1 < p.size(); i++) d.insert(abs(p[i] - p[i + 1]));
    return d.size();
}
long long countBrute(int n, int k) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    long long count = 0;
    do count += distinctDifferences(p) == k;
    while (next_permutation(p.begin(), p.end()));
    return count;
}
// method for P1 (Theorem 7.7.1's relative): alternate between the two ends of 1 ... k + 1, then continue upwards.
vector<int> alternate(int n, int k) {
    vector<int> answer;
    int lo = 1, hi = k + 1;
    for (int i = 0; i <= k; i++) answer.push_back(i % 2 == 0 ? lo++ : hi--);
    for (int v = k + 2; v <= n; v++) answer.push_back(v);
    return answer;
}
// method for P2 (Theorem 7.7.1): the two-pointer permutation for a pattern of I and D.
vector<int> matchPattern(const string& s) {
    int lo = 0, hi = s.size();
    vector<int> p;
    for (char c : s) p.push_back(c == 'I' ? lo++ : hi--);
    p.push_back(lo);
    return p;
}
bool patternExistsBrute(const string& s) {
    int n = s.size();
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    do {
        bool ok = true;
        for (int i = 0; i < n; i++) ok = ok && ((s[i] == 'I') == (p[i] < p[i + 1]));
        if (ok) return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}
int main() {
    // P1: a permutation of 1 ... 6 with exactly 4 distinct differences
    cout << "P1 brute=" << (countBrute(6, 4) > 0 ? "yes" : "no") << " method=" << (distinctDifferences(alternate(6, 4)) == 4 ? "yes" : "no") << "\n";
    // P2: the pattern IDDI
    auto q = matchPattern("IDDI");
    bool good = true;
    string s = "IDDI";
    for (int i = 0; i < 4; i++) good = good && ((s[i] == 'I') == (q[i] < q[i + 1]));
    cout << "P2 brute=" << (patternExistsBrute("IDDI") ? "yes" : "no") << " method=" << (good ? "yes" : "no") << "\n";
    // N1: how many permutations of 1 ... 7 have exactly 3 distinct differences, against one constructed permutation
    cout << "N1 brute=" << countBrute(7, 3) << " method=" << 1 << "\n";
}
