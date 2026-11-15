#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.3.4. A trie whose counts change. pass[v] = how many stored words go through v. Storing or removing one word
// changes the counts of the nodes of its own path by +1 or -1, so the cost is the length of the word.
struct CountTrie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0};
    int step(int v, char ch) {  // the child of v for the letter ch, made if it is missing
        int c = ch - 'a';
        if (!child[v][c]) {
            child[v][c] = child.size();
            child.push_back(array<int, 26>{});
            pass.push_back(0);
        }
        return child[v][c];
    }
    void add(const string& w, int delta) {  // delta = +1 stores w, -1 removes one stored copy of w
        int v = 0;
        pass[0] += delta;
        for (char ch : w) {
            v = step(v, ch);
            pass[v] += delta;
        }
    }
    int count(const string& u) {  // how many stored words begin with u
        int v = 0;
        for (char ch : u) v = step(v, ch);
        return pass[v];
    }
};
// snippet:end

int main() {
    CountTrie t;
    for (string w : {"ab", "abc", "b"}) t.add(w, +1);
    cout << "stored ab abc b: count(a) = " << t.count("a") << ", count(ab) = " << t.count("ab") << ", count(c) = " << t.count("c") << "\n";
    t.add("ab", -1);
    cout << "after removing ab: count(a) = " << t.count("a") << ", count(ab) = " << t.count("ab") << "\n";
    t.add("ab", +1);
    t.add("ab", +1);
    t.add("ab", -1);
    cout << "ab stored twice, one removed: count(ab) = " << t.count("ab") << ", count() = " << t.count("") << "\n";
    // Check (not printed): random sequences of stores and removals of words of length 1 to 3 over {a, b} give the same
    // counts as a multiset of the stored words that is searched by hand.
    mt19937 rng(7);
    for (int round = 0; round < 3000; round++) {
        CountTrie tr;
        multiset<string> stored;
        for (int op = 0; op < 12; op++) {
            string w(1 + rng() % 3, 'a');
            for (char& c : w) c = 'a' + rng() % 2;
            if (rng() % 3 && !(stored.count(w) == 0 && rng() % 2)) {
                if (rng() % 3 == 0 && stored.count(w)) {
                    tr.add(w, -1);
                    stored.erase(stored.find(w));
                } else {
                    tr.add(w, +1);
                    stored.insert(w);
                }
            }
            for (string u : {"a", "b", "aa", "ab", "ba", "bb", "aab", "abb"}) {
                int want = 0;
                for (const string& s : stored) want += s.compare(0, u.size(), u) == 0;
                if (tr.count(u) != want) return 1;
            }
        }
    }
}
