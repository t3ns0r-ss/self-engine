#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.5. C[l][r] = the fewest operations that delete all of s[l..r], an operation deleting a block of equal letters:
// the first letter goes alone, or together with a later equal letter s[k] after the part between them is gone.
int fewestOperations(const string& s) {
    int n = s.size();
    vector<vector<int>> C(n + 2, vector<int>(n + 2, 0));  // C[l][r] with 1-based l, r; an empty segment is 0
    auto get = [&](int l, int r) { return l > r ? 0 : C[l][r]; };
    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            int value = 1 + get(l + 1, r);
            for (int k = l + 1; k <= r; k++)
                if (s[k - 1] == s[l - 1]) value = min(value, get(l + 1, k - 1) + get(k, r));
            C[l][r] = value;
        }
    return get(1, n);
}
// snippet:end

int bruteOps(const string& s) {  // breadth-first search over strings, deleting one block of equal letters per step
    map<string, int> dist;
    queue<string> q;
    dist[s] = 0, q.push(s);
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        if (u.empty()) return dist[u];
        for (size_t i = 0; i < u.size();) {
            size_t j = i;
            while (j < u.size() && u[j] == u[i]) j++;
            for (size_t a = i; a < j; a++) for (size_t b = a + 1; b <= j; b++) {
                string v = u.substr(0, a) + u.substr(b);
                if (!dist.count(v)) dist[v] = dist[u] + 1, q.push(v);
            }
            i = j;
        }
    }
    return -1;
}
int main() {
    cout << "fewest operations for abaca: " << fewestOperations("abaca") << '\n';
    mt19937 rng(55);
    for (int round = 0; round < 200; round++) {
        string t;
        for (int i = 1 + rng() % 7; i > 0; i--) t += 'a' + rng() % 3;
        if (fewestOperations(t) != bruteOps(t)) return 1;
    }
}
