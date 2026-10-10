#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.4.2. The number of multiples of k in {l, ..., r}, for 1 <= l <= r and k >= 1.
long long multiplesIn(long long l, long long r, long long k) { return r / k - (l - 1) / k; }
// snippet:end

int main() {
    cout << "multiples of 7 in 20..100: " << multiplesIn(20, 100, 7) << '\n';
    cout << "multiples of 5 in 1..4: " << multiplesIn(1, 4, 5) << '\n';
    cout << "multiples of 3 in 3..3: " << multiplesIn(3, 3, 3) << '\n';
    for (int k = 1; k <= 9; k++)
        for (int l = 1; l <= 40; l++)
            for (int r = l; r <= 40; r++) {
                int count = 0;
                for (int x = l; x <= r; x++) count += x % k == 0;
                if (count != multiplesIn(l, r, k)) return 1;
            }
}
