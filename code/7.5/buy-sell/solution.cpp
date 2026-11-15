#include <bits/stdc++.h>
using namespace std;

/*
Problem: the price of a share on each of n days. On each day you may buy one share, sell one share, or do nothing; you start and end with
no shares. Print the largest profit.
Input: n, then the n prices.
Output: the largest profit.
*/


// snippet:begin
// The undo form of regret: the heap holds prices at which a share could still be bought. If the cheapest price m is below today's price p,
// sell a share bought at m (profit p - m) and push p twice: once for this sale (a later price q > p turns the profit p - m into q - m, so
// the sale today is undone and a sale at q takes its place) and once as a new purchase today.
long long bestTrades(const vector<int>& prices) {
    priority_queue<int, vector<int>, greater<int>> options;
    long long profit = 0;
    for (int p : prices) {
        if (!options.empty() && options.top() < p) {
            profit += p - options.top(), options.pop();
            options.push(p);  // the undo item of this sale
        }
        options.push(p);  // buy today
    }
    return profit;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int& x : prices) cin >> x;
    cout << bestTrades(prices) << "\n";
}
