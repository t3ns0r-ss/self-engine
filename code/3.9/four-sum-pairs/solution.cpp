/*
Problem: four lists A, B, C, D of n numbers each. Count the quadruples (i, j, k, l) with A[i] + B[j] + C[k] + D[l] = 0.
Input: n (1 <= n <= 200), then the four lists, one per line (|value| <= 2^28).
Output: the number of such quadruples.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Meet in the middle over pairs: the n^2 sums A[i] + B[j] go into one sorted list, and each C[k] + D[l] looks up its negative.
long long countZeroQuadruples(const vector<long long>& A, const vector<long long>& B, const vector<long long>& C, const vector<long long>& D) {
    vector<long long> ab;
    ab.reserve(A.size() * B.size());
    for (long long x : A) for (long long y : B) ab.push_back(x + y);
    sort(ab.begin(), ab.end());
    long long count = 0;
    for (long long x : C)
        for (long long y : D) {
            auto range = equal_range(ab.begin(), ab.end(), -(x + y));
            count += range.second - range.first;
        }
    return count;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> A(n), B(n), C(n), D(n);
    for (auto* list : {&A, &B, &C, &D}) for (auto& x : *list) cin >> x;
    cout << countZeroQuadruples(A, B, C, D) << "\n";
}
