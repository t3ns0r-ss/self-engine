#include <bits/stdc++.h>
using namespace std;

/*
Problem: buildings in a row with heights h_0, ..., h_{n-1}. Standing on building i you can move to i + 1 if h_{i+1} <= h_i for free,
and otherwise you must pay either h_{i+1} - h_i bricks or one ladder. You have `bricks` bricks and `ladders` ladders. Print the
largest index you can reach.
Input: n, bricks and ladders, then the n heights.
Output: the largest index.
*/


// snippet:begin
// Theorem 7.4.2 (covering form): every climb is first paid with bricks and kept in a heap; when the bricks run out, the largest climb
// paid so far is changed into a ladder (a payment made in the past). If no ladder is left, the walk stops at the building i.
int furthestBuilding(const vector<int>& heights, int bricks, int ladders) {
    priority_queue<int> paid;
    for (size_t i = 0; i + 1 < heights.size(); i++) {
        int climb = heights[i + 1] - heights[i];
        if (climb <= 0) continue;
        paid.push(climb), bricks -= climb;
        if (bricks < 0) {
            if (ladders == 0) return i;
            ladders--, bricks += paid.top(), paid.pop();
        }
    }
    return heights.size() - 1;
}
// snippet:end

int main() {
    int n, bricks, ladders;
    cin >> n >> bricks >> ladders;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    cout << furthestBuilding(h, bricks, ladders) << "\n";
}
