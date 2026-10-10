#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.4. The arrangements of a list with c_i copies of value i: n! / (c_1! ... c_k!), exact in 64 bits here.
long long multinomial(const vector<int>& c) {
    long long ways = 1;
    int n = 0;
    for (int ci : c) {
        for (int j = 1; j <= ci; j++) ways = ways * (++n) / j;  // multiply in C(n, ci), step by step
    }
    return ways;
}
// snippet:end

int main() {
    cout << "AAB: " << multinomial({2, 1}) << " arrangements\n";
    cout << "MISSISSIPPI: " << multinomial({1, 4, 4, 2}) << " arrangements\n";
    for (string s : {"AAB", "ABBA", "AABBC", "ABCABC"}) {
        sort(s.begin(), s.end());
        set<string> seen;
        do seen.insert(s); while (next_permutation(s.begin(), s.end()));
        map<char, int> cnt;
        for (char ch : s) cnt[ch]++;
        vector<int> c;
        for (auto [ch, k] : cnt) c.push_back(k);
        if ((long long)seen.size() != multinomial(c)) return 1;
    }
}
