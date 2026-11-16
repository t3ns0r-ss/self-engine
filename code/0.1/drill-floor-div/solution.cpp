/*
Drill (about 3 minutes). Given a and b > 0, print floor(a / b) and the remainder r with 0 <= r < b, so that a = b*q + r.
C++ division truncates toward zero, so a negative a needs a correction.
Input: q queries, each "a b" with |a| <= 10^18 and 1 <= b <= 10^18. Output: one line "q r" per query.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.1.4. `/` and `%` round toward zero; when the remainder is negative, move one step down.
pair<long long, long long> floorDivMod(long long a, long long b) {  // b > 0
    long long q = a / b, r = a % b;
    if (r < 0) {
        r += b;
        q -= 1;
    }
    return {q, r};
}
// snippet:end

int main() {
    int queries;
    cin >> queries;
    while (queries--) {
        long long a, b;
        cin >> a >> b;
        auto [q, r] = floorDivMod(a, b);
        cout << q << " " << r << "\n";
    }
}
