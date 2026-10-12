#include <bits/stdc++.h>
using namespace std;

/*
Problem: n engineers with speeds s_i and efficiencies e_i. Choose at most k of them; the performance of a team is the sum of the speeds
times the smallest efficiency in it. Print the largest performance.
Input: n and k, then the n speeds, then the n efficiencies.
Output: the largest performance.
*/


// snippet:begin
// Fix the smallest efficiency: go through the engineers from the highest efficiency down. With the current one as the smallest, the best
// team takes the k largest speeds among those seen so far (a heap with their sum).
long long bestTeam(const vector<int>& speed, const vector<int>& efficiency, int k) {
    vector<int> order(speed.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return efficiency[a] > efficiency[b]; });
    priority_queue<int, vector<int>, greater<int>> team;  // the smallest speed on top
    long long sum = 0, best = 0;
    for (int i : order) {
        team.push(speed[i]), sum += speed[i];
        if ((int)team.size() > k) sum -= team.top(), team.pop();
        best = max(best, sum * efficiency[i]);
    }
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> speed(n), efficiency(n);
    for (int& x : speed) cin >> x;
    for (int& x : efficiency) cin >> x;
    cout << bestTeam(speed, efficiency, k) << "\n";
}
