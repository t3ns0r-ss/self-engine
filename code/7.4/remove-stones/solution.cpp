#include <bits/stdc++.h>
using namespace std;

/*
Problem: piles of stones. In one operation choose a pile with x stones and remove floor(x / 2) of them; exactly k operations are made
(a pile may be chosen again). Print the least number of stones that can remain.
Input: n and k, then the n pile sizes.
Output: the least total.
*/


// snippet:begin
// Theorem 7.4.3 (a): an operation on x gains floor(x / 2) and the gains on one pile fall, so each operation goes to the largest pile.
long long remainingStones(const vector<int>& piles, int k) {
    priority_queue<int> heap(piles.begin(), piles.end());
    long long total = accumulate(piles.begin(), piles.end(), 0LL);
    while (k--) {
        int x = heap.top();
        heap.pop();
        total -= x / 2, heap.push(x - x / 2);
    }
    return total;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> piles(n);
    for (int& x : piles) cin >> x;
    cout << remainingStones(piles, k) << "\n";
}
