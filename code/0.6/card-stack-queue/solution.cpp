#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: is "(()())" properly nested? Brute: remove "()" until nothing changes. Method: a stack.
    string s = "(()())", t = s;
    for (size_t p; (p = t.find("()")) != string::npos;) t.erase(p, 2);
    stack<int> st;
    bool ok = true;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') st.push(i);
        else if (st.empty()) ok = false;
        else st.pop();
    }
    cout << "P1 brute=" << (t.empty() ? "yes" : "no") << " method=" << (ok && st.empty() ? "yes" : "no") << '\n';
    // N1: serve the most valuable of 3 9 5 first, with a plain queue. Brute: the maximum. Method: the front.
    queue<int> q;
    for (int v : {3, 9, 5}) q.push(v);
    cout << "N1 brute=" << 9 << " method=" << q.front() << '\n';
    // N2: is "([)]" properly nested when brackets of different kinds are only counted? Brute: remove pairs of the same kind.
    string u = "([)]";
    bool changed = true;
    while (changed) {
        changed = false;
        for (string pair : {"()", "[]"})
            for (size_t p; (p = u.find(pair)) != string::npos;) u.erase(p, 2), changed = true;
    }
    int depth = 0;
    bool counted = true;
    for (char c : string("([)]")) {
        depth += (c == '(' || c == '[') ? 1 : -1;
        counted &= depth >= 0;
    }
    cout << "N2 brute=" << (u.empty() ? "yes" : "no") << " method=" << (counted && depth == 0 ? "yes" : "no") << '\n';
}
