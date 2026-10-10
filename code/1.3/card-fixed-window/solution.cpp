#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {3, 1, 2, 1, 4, 1};
    // P1: the sums of all windows of length 3. Brute: add each window. Method: add the entering, remove the leaving.
    string brute, method;
    for (int l = 0; l + 3 <= 6; l++) brute += (l ? "," : "") + to_string(a[l] + a[l + 1] + a[l + 2]);
    int sum = 0;
    for (int r = 0; r < 6; r++) {
        sum += a[r];
        if (r >= 3) sum -= a[r - 3];
        if (r >= 2) method += (r > 2 ? "," : "") + to_string(sum);
    }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the maxima of the windows of length 3 in 5 1 2 4. Brute: max of each. Method: a multiset of the window.
    vector<int> b = {5, 1, 2, 4};
    brute = method = "";
    for (int l = 0; l + 3 <= 4; l++) brute += (l ? "," : "") + to_string(*max_element(b.begin() + l, b.begin() + l + 3));
    multiset<int> w;
    for (int r = 0; r < 4; r++) {
        w.insert(b[r]);
        if (r >= 3) w.erase(w.find(b[r - 3]));
        if (r >= 2) method += (r > 2 ? "," : "") + to_string(*w.rbegin());
    }
    cout << "P2 brute=" << brute << " method=" << method << '\n';
    // N1: the same maxima with one variable "maximum so far" that cannot remove the leaving element.
    method = "";
    int mx = INT_MIN;
    for (int r = 0; r < 4; r++) {
        mx = max(mx, b[r]);
        if (r >= 2) method += (r > 2 ? "," : "") + to_string(mx);
    }
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: the longest window of 3 1 2 1 4 1 with sum at most 5, answered with the best window of length exactly 2.
    int longest = 0;
    for (int l = 0; l < 6; l++) for (int r = l, s = 0; r < 6; r++) { s += a[r]; if (s <= 5) longest = max(longest, r - l + 1); }
    int fixed = 0;
    for (int l = 0; l + 2 <= 6; l++) if (a[l] + a[l + 1] <= 5) fixed = 2;
    cout << "N2 brute=" << longest << " method=" << fixed << '\n';
}
