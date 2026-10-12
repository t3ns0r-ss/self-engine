#include <bits/stdc++.h>
using namespace std;

string s;
vector<string> words;
long long go(int i) {
    if (i == (int)s.size()) return 1;
    long long total = 0;
    for (const string& w : words)
        if (s.compare(i, w.size(), w) == 0) total += go(i + w.size());
    return total % 1000000007;
}
int main() {
    int k;
    cin >> s >> k;
    words.resize(k);
    for (string& w : words) cin >> w;
    sort(words.begin(), words.end());
    words.erase(unique(words.begin(), words.end()), words.end());
    cout << go(0) % 1000000007 << "\n";
}
