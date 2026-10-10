#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.2. Is a * b > L? Answered without computing the product. Needs a >= 0 and b >= 1.
bool exceeds(long long a, long long b, long long L) { return a > L / b; }
// snippet:end

int main() {
    cout << "1000000000 * 1000000000 > 10^18: " << (exceeds(1000000000, 1000000000, 1000000000000000000LL) ? "yes" : "no") << '\n';
    cout << "1000000001 * 1000000000 > 10^18: " << (exceeds(1000000001, 1000000000, 1000000000000000000LL) ? "yes" : "no") << '\n';
    cout << "5 * 7 > 34: " << (exceeds(5, 7, 34) ? "yes" : "no") << '\n';
    for (int a = 0; a <= 40; a++)
        for (int b = 1; b <= 40; b++)
            for (int L = 0; L <= 400; L++)
                if (exceeds(a, b, L) != (a * b > L)) return 1;
}
