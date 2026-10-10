#include <bits/stdc++.h>
using namespace std;

long long weighted(vector<pair<int, int>> job) {  // (t, w): the sum of w * finishing time in the given order
    long long time = 0, sum = 0;
    for (auto [t, w] : job) sum += w * (time += t);
    return sum;
}

int main() {
    // P1: the smallest sum of finishing times of durations 3 1 2. Brute: every order. Method: shortest first.
    vector<int> a = {3, 1, 2}, s = a;
    sort(s.begin(), s.end());
    long long brute = LLONG_MAX, method = 0, time = 0;
    sort(a.begin(), a.end());  // next_permutation must start from the sorted order
    do { long long t = 0, sum = 0; for (int d : a) sum += t += d; brute = min(brute, sum); } while (next_permutation(a.begin(), a.end()));
    for (int d : s) method += time += d;
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the smallest weighted sum for jobs (t, w) = (2, 1) and (1, 3). Brute: both orders. Method: sort by t / w.
    vector<pair<int, int>> j = {{2, 1}, {1, 3}}, k = j;
    brute = min(weighted(j), weighted({j[1], j[0]}));
    sort(k.begin(), k.end(), [](pair<int, int> x, pair<int, int> y) { return x.first * y.second < y.first * x.second; });
    cout << "P2 brute=" << brute << " method=" << weighted(k) << '\n';
    // N1: jobs (1, 1) and (2, 10) with weights; shortest first ignores the weights.
    vector<pair<int, int>> m = {{1, 1}, {2, 10}};
    brute = min(weighted(m), weighted({m[1], m[0]}));
    cout << "N1 brute=" << brute << " method=" << weighted(m) << '\n';
    // N2: can both jobs (duration 3, deadline 3) and (duration 1, deadline 10) finish on time? Shortest first runs the
    // second job first, so the first finishes at 4 > 3.
    int finishShort = 1 + 3;
    bool byDeadline = (3 <= 3) && (3 + 1 <= 10), shortestFirst = finishShort <= 3;
    cout << "N2 brute=" << (byDeadline ? "yes" : "no") << " method=" << (shortestFirst ? "yes" : "no") << '\n';
}
