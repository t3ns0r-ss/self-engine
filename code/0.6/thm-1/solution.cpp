#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.1. push_back with capacity doubling: the number of element copies made by n calls.
long long copiesForPushBack(int n) {
    long long copies = 0, capacity = 1, size = 0;
    for (int i = 0; i < n; i++) {
        if (size == capacity) {  // full: copy everything into twice the space
            copies += size;
            capacity *= 2;
        }
        size++;
    }
    return copies;
}
// snippet:end

int main() {
    for (int n : {5, 8, 1000}) cout << n << " push_back calls: " << copiesForPushBack(n) << " copies\n";
    for (int n = 1; n <= 5000; n++)
        if (copiesForPushBack(n) >= 2LL * n) return 1;  // fewer than 2n copies in all
}
