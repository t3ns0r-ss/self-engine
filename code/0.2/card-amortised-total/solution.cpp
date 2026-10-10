#include <bits/stdc++.h>
using namespace std;

// Inner iterations of the block loop on s. restart = true: the next block starts at i + 1 instead of j.
long long inner(const string& s, bool restart) {
    int n = s.size(), i = 0;
    long long steps = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++, steps++;
        i = restart ? i + 1 : j;
    }
    return steps;
}

int main() {
    // P1: "aabccc", the next block starts at j. Brute: count the inner iterations. Method: n.
    string s = "aabccc";
    cout << "P1 brute=" << inner(s, false) << " method=" << s.size() << '\n';
    // N1: "aaaa" with the next block starting at i + 1: the inner scan restarts.
    s = "aaaa";
    cout << "N1 brute=" << inner(s, true) << " method=" << s.size() << '\n';
    // N2: for each of 5 positions, scan to the end of the array.
    long long steps = 0;
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++) steps++;
    cout << "N2 brute=" << steps << " method=" << 5 << '\n';
}
