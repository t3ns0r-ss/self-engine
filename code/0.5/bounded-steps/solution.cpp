/*
Problem: count the sequences c_0 .. c_{L-1} with every c_p in 1..M and |c_p - c_{p-1}| <= D for p >= 1,
and print them all in lexicographic order when there are at most 50 of them.
Input: L M D (1 <= L <= 8, 1 <= M <= 8, 0 <= D < M).
Output: the count, then the sequences if the count is at most 50.
*/
#include <bits/stdc++.h>
using namespace std;

int L, M, D;
vector<int> c;
vector<vector<int>> found;

void rec(int pos) {
    if (pos == L) {  // base case: a complete sequence (Theorem 0.5.4)
        found.push_back(c);
        return;
    }
    for (int v = 1; v <= M; v++) {
        if (pos > 0 && abs(v - c[pos - 1]) > D) continue;  // the choices depend on the previous one
        c[pos] = v;
        rec(pos + 1);
    }
}

int main() {
    cin >> L >> M >> D;
    c.assign(L, 0);
    rec(0);
    cout << found.size() << "\n";
    if (found.size() <= 50)
        for (auto& s : found)
            for (int i = 0; i < L; i++) cout << s[i] << (i + 1 < L ? ' ' : '\n');
}
