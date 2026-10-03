#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> out;
    for (int l = 0; l + k <= n; l++) out.push_back(*max_element(a.begin() + l, a.begin() + l + k));
    for (int i = 0; i < (int)out.size(); i++) cout << out[i] << (i + 1 < (int)out.size() ? ' ' : '\n');
}
