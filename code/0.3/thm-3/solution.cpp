#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.3. One pass with the state "opens minus closes so far": the maximum depth if the string
// is a valid bracket sequence, otherwise -1.
int bracketDepth(const string& s) {
    int depth = 0, best = 0;
    bool ok = true;
    for (char ch : s) {
        depth += (ch == '(') ? 1 : -1;
        if (depth < 0) ok = false;  // a ')' with nothing open: no later character can fix it
        best = max(best, depth);
    }
    return (ok && depth == 0) ? best : -1;
}
// snippet:end

int main() {
    for (string s : {"(()())", "())(", "(()"}) {
        int d = bracketDepth(s);
        cout << s << ": " << (d >= 0 ? "valid, depth " + to_string(d) : "not valid") << '\n';
    }
    for (int len = 0; len <= 10; len++)  // every string of brackets up to length 10 against repeated removal of "()"
        for (int code = 0; code < (1 << len); code++) {
            string s, t;
            for (int i = 0; i < len; i++) s += (code >> i & 1) ? '(' : ')';
            t = s;
            for (size_t p; (p = t.find("()")) != string::npos;) t.erase(p, 2);
            int best = 0, cur = 0;
            for (char ch : s) cur += ch == '(' ? 1 : -1, best = max(best, cur);
            if (bracketDepth(s) != (t.empty() ? best : -1)) return 1;
        }
}
