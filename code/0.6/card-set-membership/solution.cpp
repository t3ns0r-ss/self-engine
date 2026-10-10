#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the distinct values of 3 1 3 3. Brute: sort and count the changes. Method: a set.
    vector<int> a = {3, 1, 3, 3}, s = a;
    sort(s.begin(), s.end());
    int brute = unique(s.begin(), s.end()) - s.begin();
    cout << "P1 brute=" << brute << " method=" << set<int>(a.begin(), a.end()).size() << '\n';
    // P2: has some value appeared twice in 4 2 7 2? Brute: compare all pairs. Method: a set of the values seen.
    vector<int> b = {4, 2, 7, 2};
    bool any = false, dup = false;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) any |= b[i] == b[j];
    set<int> seen;
    for (int x : b) { dup |= seen.count(x) > 0; seen.insert(x); }
    cout << "P2 brute=" << (any ? "yes" : "no") << " method=" << (dup ? "yes" : "no") << '\n';
    // N1: is there a repeated value within distance 1 in 1 2 1? Brute: neighbours. Method: any repeat at all (a set).
    vector<int> c = {1, 2, 1};
    bool near = false, anyRepeat = false;
    for (int i = 0; i + 1 < 3; i++) near |= c[i] == c[i + 1];
    set<int> seen2;
    for (int x : c) { anyRepeat |= seen2.count(x) > 0; seen2.insert(x); }
    cout << "N1 brute=" << (near ? "yes" : "no") << " method=" << (anyRepeat ? "yes" : "no") << '\n';
    // N2: how many times does 3 occur in 3 1 3 3? Brute: count. Method: set.count(3).
    cout << "N2 brute=" << count(a.begin(), a.end(), 3) << " method=" << set<int>(a.begin(), a.end()).count(3) << '\n';
}
