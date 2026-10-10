#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: tests of sizes 3, 5, 2. Brute: count the steps of a program that loops over each test's own array.
    // Method: the sum of the sizes (Theorem 0.1.3).
    vector<int> sizes = {3, 5, 2};
    long long counted = 0, sum = 0;
    for (int n : sizes) {
        for (int i = 0; i < n; i++) counted++;
        sum += n;
    }
    cout << "P1 brute=" << counted << " method=" << sum << '\n';
    // N1: 10000 tests of size 20 (sum 200000), but every test clears a global array of 200000 entries.
    // Brute: the steps really taken. Method: the sum of the sizes, which is what the card would predict.
    long long taken = 0, predicted = 0;
    for (int t = 0; t < 10000; t++) taken += 200000, predicted += 20;
    cout << "N1 brute=" << taken << " method=" << predicted << '\n';
    // N2: three "tests" that are really operations on one shared total: add 5, add 3, add 2; print the total each time.
    int shared = 0, perTest = 0;
    string correct, reset;
    for (int x : {5, 3, 2}) {
        shared += x;
        perTest = x;  // a variable declared inside the test loop starts again from 0 every time
        correct += (correct.empty() ? "" : ",") + to_string(shared);
        reset += (reset.empty() ? "" : ",") + to_string(perTest);
    }
    cout << "N2 brute=" << correct << " method=" << reset << '\n';
}
