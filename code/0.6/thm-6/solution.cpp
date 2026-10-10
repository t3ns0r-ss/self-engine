#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.6. Is the bracket string properly nested? Push the position of each '(' and pop at each ')'.
bool nested(const string& s) {
    stack<int> open;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') open.push(i);
        else if (open.empty()) return false;  // a ')' with nothing to match
        else open.pop();
    }
    return open.empty();
}
// snippet:end

int main() {
    for (string s : {"(())", "(()", "())("}) cout << s << ": " << (nested(s) ? "yes" : "no") << '\n';
    for (int len = 0; len <= 12; len++)  // against repeated removal of "()"
        for (int code = 0; code < (1 << len); code++) {
            string s, t;
            for (int i = 0; i < len; i++) s += (code >> i & 1) ? '(' : ')';
            t = s;
            for (size_t p; (p = t.find("()")) != string::npos;) t.erase(p, 2);
            if (nested(s) != t.empty()) return 1;
        }
}
