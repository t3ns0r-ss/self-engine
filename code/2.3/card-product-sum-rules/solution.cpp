#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: strings of length 3 over {a, b, c} with no two equal neighbours. Brute: all 27. Method: 3 * 2 * 2.
    int brute = 0;
    for (int code = 0; code < 27; code++) {
        int x = code % 3, y = code / 3 % 3, z = code / 9;
        brute += x != y && y != z;
    }
    cout << "P1 brute=" << brute << " method=" << 3 * 2 * 2 << '\n';
    // N1: the committees of 2 people out of 4, counted as "4 choices for the first, 3 for the second".
    set<pair<int, int>> committees;
    for (int a = 0; a < 4; a++) for (int b = 0; b < 4; b++) if (a != b) committees.insert({min(a, b), max(a, b)});
    cout << "N1 brute=" << committees.size() << " method=" << 4 * 3 << '\n';
    // N2: strings of length 3 over {a, b, c} using at most two different letters, counted as 3 * 2 * 2.
    int atMostTwo = 0;
    for (int code = 0; code < 27; code++) {
        set<int> s = {code % 3, code / 3 % 3, code / 9};
        atMostTwo += s.size() <= 2;
    }
    cout << "N2 brute=" << atMostTwo << " method=" << 3 * 2 * 2 << '\n';
}
