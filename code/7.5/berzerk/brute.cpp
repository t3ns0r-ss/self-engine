#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> steps[2];
    for (int who = 0; who < 2; who++) {
        int k;
        cin >> k;
        steps[who].resize(k);
        for (int& x : steps[who]) cin >> x;
    }
    // result[p][who]: 0 = loop, 1 = win, 2 = lose for the player `who` to move at p; repeat the rules until nothing changes
    vector<array<int, 2>> r(n + 1, {0, 0});
    r[1] = {2, 2};
    for (bool changed = true; changed;) {
        changed = false;
        for (int p = 2; p <= n; p++)
            for (int who = 0; who < 2; who++) {
                if (r[p][who]) continue;
                bool anyLose = false, allWin = true;
                for (int x : steps[who]) {
                    int q = (p - 1 + x) % n + 1;
                    anyLose |= r[q][1 - who] == 2, allWin &= r[q][1 - who] == 1;
                }
                if (anyLose) r[p][who] = 1, changed = true;
                else if (allWin) r[p][who] = 2, changed = true;
            }
    }
    const char* name[] = {"Loop", "Win", "Lose"};
    for (int first = 0; first < 2; first++)
        for (int p = 2; p <= n; p++) cout << name[r[p][first]] << (p < n ? " " : "\n");
}
