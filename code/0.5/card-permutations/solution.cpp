#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the cheapest order of 3 places, cost w[i][j] = |i - j| * 10 + (i > j). Brute: the 6 orders written as indices.
    int w[3][3];
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) w[i][j] = abs(i - j) * 10 + (i > j);
    int ord[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
    int brute = INT_MAX, method = INT_MAX;
    for (auto& o : ord) brute = min(brute, w[o[0]][o[1]] + w[o[1]][o[2]]);
    vector<int> v = {0, 1, 2};
    do method = min(method, w[v[0]][v[1]] + w[v[1]][v[2]]); while (next_permutation(v.begin(), v.end()));
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // N1: choose 2 of 4 items (order irrelevant). Brute: the pairs. Method: every order of 2 of the 4 items.
    cout << "N1 brute=" << 4 * 3 / 2 << " method=" << 4 * 3 << '\n';
    // N2: the arrangements of 3 2 1, where next_permutation starts from this unsorted order.
    vector<int> u = {3, 2, 1};
    int count = 0;
    do count++; while (next_permutation(u.begin(), u.end()));
    cout << "N2 brute=" << 6 << " method=" << count << '\n';
}
