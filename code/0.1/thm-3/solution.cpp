#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.3. Steps of a program that works only on each test's own size n, and of one that
// clears an array of M entries in every test.
long long stepsOwnSize(const vector<int>& n) {
    long long steps = 0;
    for (int x : n) steps += x;
    return steps;
}
long long stepsClearing(const vector<int>& n, long long M) { return (long long)n.size() * M; }
// snippet:end

int main() {
    vector<int> small = {3, 5, 2}, many(10000, 20);
    cout << "sizes 3 5 2, M = 200000: own size " << stepsOwnSize(small) << ", clearing " << stepsClearing(small, 200000) << '\n';
    cout << "10000 tests of size 20, M = 200000: own size " << stepsOwnSize(many) << ", clearing " << stepsClearing(many, 200000) << '\n';
    long long counted = 0;  // the clearing program, run for real on the small input
    for (size_t i = 0; i < small.size(); i++)
        for (int j = 0; j < 1000; j++) counted++;
    if (counted != stepsClearing(small, 1000)) return 1;
}
