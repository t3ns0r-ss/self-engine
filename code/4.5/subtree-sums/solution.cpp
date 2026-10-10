/*
Problem: sizes of folders.
Input: n, then n numbers a_1..a_n (the files in folder i, 0 <= a_i <= 10^9), then n - 1 numbers p_2..p_n: folder i lies inside
folder p_i, and p_i < i (folder 1 is the root).
Output: n numbers: for each folder, the number of files in it and in all folders below it.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.5.2 when every parent has a smaller number than its child: the numbers 1..n are already an order with parents first,
// so the backward pass is a loop from n down to 2. parent[i] is defined for i >= 2; vertices are 1..n.
vector<long long> subtreeSums(const vector<int>& parent, vector<long long> sum) {
    int n = sum.size() - 1;
    for (int i = n; i >= 2; i--) sum[parent[i]] += sum[i];  // sum[i] is complete: all its children have larger numbers
    return sum;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    auto sum = subtreeSums(parent, a);
    for (int i = 1; i <= n; i++) cout << sum[i] << (i < n ? " " : "\n");
}
