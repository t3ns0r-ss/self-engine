#include <bits/stdc++.h>
using namespace std;

/*
Problem: n piles of stones, n even (n up to 50, sizes up to 50). A move chooses exactly n / 2 non-empty piles and removes a positive number of
stones from each of them. The player who cannot move loses; Alice moves first. Print Alice or Bob (the winner).
Input: n, then the n sizes.
Output: Alice or Bob.
*/


// snippet:begin
// A pattern found with the brute force and proved by induction: let m be the smallest size and c the number of piles of that size. The player
// to move loses exactly when c > n / 2. If c <= n / 2, n / 2 piles above m can be cut down to m, which leaves more than n / 2 piles of
// size m; if c > n / 2, every move touches only n / 2 piles, so it makes some pile smaller than m, and at most n / 2 piles have the new minimum.
string winner(const vector<int>& piles) {
    int smallest = *min_element(piles.begin(), piles.end());
    int count = count_if(piles.begin(), piles.end(), [&](int x) { return x == smallest; });
    return count > (int)piles.size() / 2 ? "Bob" : "Alice";
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << winner(a) << "\n";
}
