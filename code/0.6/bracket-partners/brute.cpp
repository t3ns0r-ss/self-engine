// Repeatedly deletes an adjacent matching pair (an innermost pair) and records the two positions.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<pair<char, int>> rest;
    for (int i = 0; i < n; i++) rest.push_back({s[i], i});
    vector<int> partner(n, -1);
    auto match = [](char a, char b) { return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}'); };
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i + 1 < rest.size(); i++)
            if (match(rest[i].first, rest[i + 1].first)) {
                partner[rest[i].second] = rest[i + 1].second;
                partner[rest[i + 1].second] = rest[i].second;
                rest.erase(rest.begin() + i, rest.begin() + i + 2);
                changed = true;
                break;
            }
    }
    if (!rest.empty()) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << partner[i] << (i + 1 < n ? ' ' : '\n');
}
