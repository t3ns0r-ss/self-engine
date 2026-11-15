#include <bits/stdc++.h>
using namespace std;

struct CountTrie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0};
    vector<bool> blocked = {false};
    int step(int v, char ch) {
        int c = ch - 'a';
        if (!child[v][c]) {
            child[v][c] = child.size();
            child.push_back(array<int, 26>{});
            pass.push_back(0);
            blocked.push_back(false);
        }
        return child[v][c];
    }
    // the live strings of Y (type 2) after the queries, with strings of X (type 1) blocking their beginnings
    static int alive(const vector<pair<int, string>>& queries) {
        CountTrie t;
        for (const auto& [type, s] : queries) {
            vector<int> path = {0};
            int v = 0;
            bool covered = false;
            for (char ch : s) {
                v = t.step(v, ch);
                if (t.blocked[v]) covered = true;
                path.push_back(v);
            }
            if (covered) continue;
            if (type == 2) {
                for (int u : path) t.pass[u]++;
            } else {
                int k = t.pass[v];
                for (int u : path) t.pass[u] -= k;
                t.blocked[v] = true;
            }
        }
        return t.pass[0];
    }
};

int main() {
    {
        // P1: Y = ab, abc, b and then the prefix ab goes into X.
        vector<pair<int, string>> q = {{2, "ab"}, {2, "abc"}, {2, "b"}, {1, "ab"}};
        int brute = 0;
        for (string y : {"ab", "abc", "b"}) brute += y.compare(0, 2, "ab") != 0;
        cout << "P1 brute=" << brute << " method=" << CountTrie::alive(q) << "\n";
    }
    {
        // P2: Y = a, ab, ab, c; then the prefix a goes into X and a later ab is refused.
        vector<pair<int, string>> q = {{2, "a"}, {2, "ab"}, {2, "ab"}, {2, "c"}, {1, "a"}, {2, "ab"}};
        int brute = 0;
        for (string y : {"a", "ab", "ab", "c", "ab"}) brute += y.compare(0, 1, "a") != 0;
        cout << "P2 brute=" << brute << " method=" << CountTrie::alive(q) << "\n";
    }
    {
        // N1: the banned string bc is a suffix, not a prefix; the trie of beginnings does not see it.
        vector<pair<int, string>> q = {{2, "abc"}, {2, "xbc"}, {1, "bc"}};
        int brute = 0;
        for (string y : {"abc", "xbc"}) brute += y.size() < 2 || y.compare(y.size() - 2, 2, "bc") != 0;
        cout << "N1 brute=" << brute << " method=" << CountTrie::alive(q) << "\n";
    }
}
