#include <bits/stdc++.h>
using namespace std;

int fewestOperations(const string& s) {
    int n = s.size();
    vector<vector<int>> C(n + 2, vector<int>(n + 2, 0));
    auto get = [&](int l, int r) { return l > r ? 0 : C[l][r]; };
    for (int len = 1; len <= n; len++) for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        int value = 1 + get(l + 1, r);
        for (int k = l + 1; k <= r; k++) if (s[k - 1] == s[l - 1]) value = min(value, get(l + 1, k - 1) + get(k, r));
        C[l][r] = value;
    }
    return get(1, n);
}
int bruteOps(const string& s) {
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
    // P1: abaca. P2: aba. Brute: breadth-first search over strings, one block of equal letters deleted per step.
    cout << "P1 brute=" << bruteOps("abaca") << " method=" << fewestOperations("abaca") << '\n';
    cout << "P2 brute=" << bruteOps("aba") << " method=" << fewestOperations("aba") << '\n';
    // N1: delete abab completely when only adjacent equal PAIRS may be deleted (a stack simulation): impossible, -1.
    string s = "abab", st;
    for (char c : s) { if (!st.empty() && st.back() == c) st.pop_back(); else st += c; }
    cout << "N1 brute=" << (st.empty() ? 0 : -1) << " method=" << fewestOperations(s) << '\n';
}
