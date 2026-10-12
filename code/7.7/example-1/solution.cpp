#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 667 Beautiful Arrangement II. Given n and k with 1 <= k < n, construct a list of the numbers 1 ... n in which the n - 1 absolute
differences of neighbours contain exactly k distinct values. Any valid list is accepted.
Input: n and k.
Output: OK if the program's list passes its own check, BAD otherwise.
*/

// snippet:begin
// The first k + 1 values alternate between the two ends of 1 ... k + 1, so the differences are k, k - 1, ..., 1; then k + 2, ..., n in order add
// only the difference 1 (or a difference already seen).
vector<int> constructList(int n, int k) {
    vector<int> answer;
    int lo = 1, hi = k + 1;
    for (int i = 0; i <= k; i++) answer.push_back(i % 2 == 0 ? lo++ : hi--);
    for (int v = k + 2; v <= n; v++) answer.push_back(v);
    return answer;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    auto a = constructList(n, k);
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    bool ok = (int)a.size() == n;
    for (int i = 0; ok && i < n; i++) ok = sorted[i] == i + 1;
    set<int> differences;
    for (int i = 0; ok && i + 1 < n; i++) differences.insert(abs(a[i] - a[i + 1]));
    cout << (ok && (int)differences.size() == k ? "OK" : "BAD") << "\n";
}
