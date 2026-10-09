// Card example unit (PLAN.md Section 8.6): the numbers behind the inline examples of the card
// "Nearest greater or smaller element". Prints "P<k>" lines for positive and "N<k>" lines for negative
// examples, each with the brute-force answer and the answer of the card's method.
#include <bits/stdc++.h>
using namespace std;

// The card's method: monotonic stack, next strictly greater position (-1 if none).
vector<int> stack_next(const vector<int>& a) {
    vector<int> nxt(a.size(), -1), st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!st.empty() && a[st.back()] < a[i]) nxt[st.back()] = i, st.pop_back();
        st.push_back(i);
    }
    return nxt;
}

string join(const vector<int>& v) {
    string s;
    for (int i = 0; i < (int)v.size(); i++) s += (i ? "," : "") + to_string(v[i]);
    return s;
}

int main() {
    // P1: days to wait for a strictly warmer day.
    vector<int> a = {5, 3, 8, 4, 2, 9}, brute(a.size(), 0), method = stack_next(a);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = i + 1; j < (int)a.size(); j++)
            if (a[j] > a[i]) { brute[i] = j - i; break; }
    for (int i = 0; i < (int)a.size(); i++) method[i] = method[i] < 0 ? 0 : method[i] - i;
    cout << "P1 brute=" << join(brute) << " method=" << join(method) << '\n';

    // N1: the array changes after the stack was built. Query: next greater of position 1 of (3, 1, 2),
    // asked again after a[2] becomes 0. The stack's stored answer is stale.
    vector<int> b = {3, 1, 2};
    int stale = stack_next(b)[1];
    b[2] = 0;
    int fresh = -1;
    for (int j = 2; j < 3; j++) if (b[j] > b[1]) { fresh = j; break; }
    cout << "N1 brute=" << fresh << " method=" << stale << '\n';

    // N2: nearest j > 0 with a_j divisible by a_0, for (2, 3, 4). Popping on "greater" discards 2 too early.
    vector<int> c = {2, 3, 4};
    int want = -1;
    for (int j = 1; j < 3; j++) if (c[j] % c[0] == 0) { want = j; break; }
    cout << "N2 brute=" << want << " method=" << stack_next(c)[0] << '\n';
}
