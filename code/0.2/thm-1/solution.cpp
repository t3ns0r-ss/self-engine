#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.1. k nested loops with bounds m_1 .. m_k take m_1 * ... * m_k innermost steps;
// about 10^8 steps fit in one second.
long long nestedSteps(const vector<long long>& bounds) {
    long long steps = 1;
    for (long long m : bounds) steps *= m;
    return steps;
}
bool fits(long long steps, double seconds) { return steps <= 1e8 * seconds; }
// snippet:end

int main() {
    for (auto [bounds, sec] : {pair{vector<long long>{5000, 5000}, 1.0}, pair{vector<long long>{200000, 200000}, 2.0}, pair{vector<long long>{500, 500, 500}, 2.0}}) {
        long long steps = nestedSteps(bounds);
        for (size_t i = 0; i < bounds.size(); i++) cout << (i ? " x " : "loops ") << bounds[i];
        cout << ": " << steps << " steps, fits in " << sec << " s: " << (fits(steps, sec) ? "yes" : "no") << '\n';
    }
    long long counted = 0;  // the product against the loops run for real
    for (int a = 0; a < 7; a++)
        for (int b = 0; b < 5; b++)
            for (int c = 0; c < 3; c++) counted++;
    if (counted != nestedSteps({7, 5, 3})) return 1;
}
