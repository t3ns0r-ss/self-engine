#include <bits/stdc++.h>
using namespace std;

vector<int> placeByPairs(const vector<int>& a, bool indexDescending) {
    int n = a.size();
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) v[i] = {a[i], indexDescending ? -i : i};
    sort(v.begin(), v.end());
    vector<int> place(n);
    for (int k = 0; k < n; k++) place[indexDescending ? -v[k].second : v[k].second] = k;
    return place;
}

int main() {
    // P1: the place of every element of 50 10 50 7 (equal values by index). Brute: count the smaller ones.
    vector<int> a = {50, 10, 50, 7};
    vector<int> place = placeByPairs(a, false);
    string brute, method;
    for (int i = 0; i < 4; i++) {
        int smaller = 0;
        for (int j = 0; j < 4; j++) smaller += a[j] < a[i] || (a[j] == a[i] && j < i);
        brute += (i ? "," : "") + to_string(smaller);
        method += (i ? "," : "") + to_string(place[i]);
    }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the same for 3 1 2.
    vector<int> b = {3, 1, 2};
    place = placeByPairs(b, false);
    brute = method = "";
    for (int i = 0; i < 3; i++) {
        int smaller = 0;
        for (int j = 0; j < 3; j++) smaller += b[j] < b[i] || (b[j] == b[i] && j < i);
        brute += (i ? "," : "") + to_string(smaller);
        method += (i ? "," : "") + to_string(place[i]);
    }
    cout << "P2 brute=" << brute << " method=" << method << '\n';
    // N1: the original index of the smallest element of 50 10 50 7. Method: sort the values alone and read the
    // position of the smallest in the sorted array as if it were its index.
    vector<int> c = {50, 10, 50, 7};
    int index = min_element(c.begin(), c.end()) - c.begin();
    vector<int> s = c;
    sort(s.begin(), s.end());
    int position = min_element(s.begin(), s.end()) - s.begin();
    cout << "N1 brute=" << index << " method=" << position << '\n';
    // N2: the place of the element at index 2 of 50 10 50 7 when equal values must come by DESCENDING index.
    int want = 0;
    for (int j = 0; j < 4; j++) want += c[j] < c[2] || (c[j] == c[2] && j > 2);
    cout << "N2 brute=" << want << " method=" << placeByPairs(c, false)[2] << '\n';
}
