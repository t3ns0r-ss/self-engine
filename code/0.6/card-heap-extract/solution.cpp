#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: halve the largest of 8 3 5 three times (rounding down); the sum left. Brute: scan for the largest each time.
    vector<int> a = {8, 3, 5}, a0 = a;
    for (int i = 0; i < 3; i++) *max_element(a.begin(), a.end()) /= 2;
    priority_queue<int> pq(a0.begin(), a0.end());
    for (int i = 0; i < 3; i++) { int x = pq.top(); pq.pop(); pq.push(x / 2); }
    int sum = 0;
    for (; !pq.empty(); pq.pop()) sum += pq.top();
    cout << "P1 brute=" << accumulate(a.begin(), a.end(), 0) << " method=" << sum << '\n';
    // P2: merge the two smallest of 1 2 3 until one pile is left, paying their total. Brute: both greedy orders by hand.
    vector<int> v123 = {1, 2, 3};
    priority_queue<int, vector<int>, greater<int>> mn(v123.begin(), v123.end());
    int cost = 0;
    while (mn.size() > 1) { int x = mn.top(); mn.pop(); int y = mn.top(); mn.pop(); cost += x + y; mn.push(x + y); }
    cout << "P2 brute=" << (1 + 2) + (3 + 3) << " method=" << cost << '\n';
    // N1: the most expensive ticket at most 8 among 3 7 10. Brute: scan. Method: the top of a priority queue.
    vector<int> v3710 = {3, 7, 10};
    priority_queue<int> t(v3710.begin(), v3710.end());
    int best = -1;
    for (int v : {3, 7, 10}) if (v <= 8) best = max(best, v);
    cout << "N1 brute=" << best << " method=" << t.top() << '\n';
    // N2: merge the two LARGEST of 1 2 3 each time, paying their total.
    priority_queue<int> mx(v123.begin(), v123.end());
    int bad = 0;
    while (mx.size() > 1) { int x = mx.top(); mx.pop(); int y = mx.top(); mx.pop(); bad += x + y; mx.push(x + y); }
    cout << "N2 brute=" << cost << " method=" << bad << '\n';
}
