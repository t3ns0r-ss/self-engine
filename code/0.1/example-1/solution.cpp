/*
Problem: CSES 1068 Weird Algorithm. Starting from n, halve it if even, else replace it by 3n + 1,
until it reaches 1; print every value.
Input: n (1 <= n <= 10^6).
Output: the values, separated by spaces.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The values of the process, starting from n. They exceed 2^31 for some n below 10^6, so long long.
vector<long long> weirdSequence(long long n) {
    vector<long long> seq = {n};
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        seq.push_back(n);
    }
    return seq;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    vector<long long> seq = weirdSequence(n);
    for (int i = 0; i < (int)seq.size(); i++) cout << seq[i] << (i + 1 < (int)seq.size() ? " " : "\n");
}
