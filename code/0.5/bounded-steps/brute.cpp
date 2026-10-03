// Counts in base M: every number 0 .. M^L - 1 is one sequence (digits + 1); keeps the valid ones.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int L, M, D;
    cin >> L >> M >> D;
    long long total = 1;
    for (int i = 0; i < L; i++) total *= M;
    vector<vector<int>> found;
    for (long long x = 0; x < total; x++) {
        vector<int> s(L);
        long long y = x;
        for (int i = L - 1; i >= 0; i--) {  // the last position is the lowest digit
            s[i] = (int)(y % M) + 1;
            y /= M;
        }
        bool ok = true;
        for (int i = 1; i < L; i++) ok = ok && abs(s[i] - s[i - 1]) <= D;
        if (ok) found.push_back(s);
    }
    cout << found.size() << "\n";
    if (found.size() <= 50)
        for (auto& s : found)
            for (int i = 0; i < L; i++) cout << s[i] << (i + 1 < L ? ' ' : '\n');
}
