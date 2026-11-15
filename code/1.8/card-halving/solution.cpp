#include <bits/stdc++.h>
using namespace std;

// Card example unit: the numbers of the inline examples of the card "halving". Not shown in the lesson.
// brute = the hidden number by asking every question "x <= 1?", "x <= 2?", ... until the first yes.
// method = halving (Theorem 1.8.1) with the replies of the judge given as a function.

template <class Ask>
int halving(int n, Ask ask) {
    int lo = 0, hi = n;
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (ask(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    // P1: hidden number 37 in 1..100; the judge answers "x <= m?".
    {
        int x = 37, n = 100;
        auto ask = [&](int m) { return x <= m; };
        int brute = 0;
        for (int m = 1; m <= n && !brute; m++)
            if (ask(m)) brute = m;
        cout << "P1 brute=" << brute << " method=" << halving(n, ask) << "\n";
    }
    // N1: hidden number 3 in 1..8; the judge only answers "x == m?", so a "no" says nothing about the side.
    {
        int x = 3, n = 8;
        auto ask = [&](int m) { return x == m; };
        int brute = 0;
        for (int m = 1; m <= n && !brute; m++)
            if (x == m) brute = m;
        cout << "N1 brute=" << brute << " method=" << halving(n, ask) << "\n";
    }
    return 0;
}
