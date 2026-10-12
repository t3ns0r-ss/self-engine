#include <bits/stdc++.h>
using namespace std;

struct Trie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0}, end = {0};
    void insert(const string& w) {
        int v = 0;
        pass[0]++;
        for (char ch : w) {
            int c = ch - 'a';
            if (!child[v][c]) {
                child[v][c] = child.size();
                child.push_back(array<int, 26>{});
                pass.push_back(0);
                end.push_back(0);
            }
            v = child[v][c];
            pass[v]++;
        }
        end[v]++;
    }
};

int main() {
    {
        vector<string> words = {"ab", "abc", "abd", "b"};
        int brute = 0;
        for (const string& w : words) brute += w.compare(0, 2, "ab") == 0;
        Trie t;
        for (const string& w : words) t.insert(w);
        int v = 0;
        for (char c : string("ab")) v = t.child[v][c - 'a'];
        cout << "P1 brute=" << brute << " method=" << t.pass[v] << "\n";
    }
    {
        vector<string> words = {"ab", "ac", "b"};
        long long brute = 0, method = 0;
        for (size_t i = 0; i < words.size(); i++)
            for (size_t j = i + 1; j < words.size(); j++) {
                size_t k = 0;
                while (k < words[i].size() && k < words[j].size() && words[i][k] == words[j][k]) k++;
                brute += k;
            }
        Trie t;
        for (const string& w : words) t.insert(w);
        for (size_t v = 1; v < t.pass.size(); v++) method += (long long)t.pass[v] * (t.pass[v] - 1) / 2;
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: the question asks for words that contain bc anywhere; the trie of the words answers prefix questions only.
        vector<string> words = {"abc", "xbc", "ybc"};
        int brute = 0;
        for (const string& w : words) brute += w.find("bc") != string::npos;
        Trie t;
        for (const string& w : words) t.insert(w);
        int v = 0, method = 0;
        for (char c : string("bc")) {
            v = t.child[v][c - 'a'];
            if (!v) break;
        }
        method = v ? t.pass[v] : 0;
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
