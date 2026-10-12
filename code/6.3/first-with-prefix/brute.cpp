#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    cin >> q;
    while (q--) {
        string u;
        cin >> u;
        int answer = -1;
        for (int i = 0; i < n && answer < 0; i++)
            if (words[i].compare(0, u.size(), u) == 0) answer = i + 1;
        cout << answer << "\n";
    }
}
