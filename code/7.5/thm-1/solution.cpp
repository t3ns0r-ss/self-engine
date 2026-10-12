#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.5.1. A game on a graph: a move goes along an edge, and the player who cannot move loses. The result of a position is WIN
// (the player to move wins), LOSE or DRAW. A position without moves is LOSE; one with a move to a LOSE position is WIN; one whose
// moves all lead to WIN positions is LOSE. left[v] counts the moves of v not yet seen to lead to a WIN position.
enum { DRAW, WIN, LOSE };
vector<int> solveGame(const vector<vector<int>>& moves) {
    int n = moves.size();
    vector<vector<int>> back(n);
    vector<int> left(n), result(n, DRAW);
    queue<int> ready;
    for (int v = 0; v < n; v++) {
        left[v] = moves[v].size();
        for (int u : moves[v]) back[u].push_back(v);
        if (left[v] == 0) result[v] = LOSE, ready.push(v);
    }
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        for (int v : back[u]) {
            if (result[v] != DRAW) continue;
            if (result[u] == LOSE) result[v] = WIN, ready.push(v);
            else if (--left[v] == 0) result[v] = LOSE, ready.push(v);
        }
    }
    return result;
}
// snippet:end

vector<int> bruteGame(const vector<vector<int>>& moves) {  // repeat the three rules on all positions until nothing changes
    int n = moves.size();
    vector<int> result(n, DRAW);
    for (bool changed = true; changed;) {
        changed = false;
        for (int v = 0; v < n; v++) {
            if (result[v] != DRAW) continue;
            bool anyLose = false, allWin = true;
            for (int u : moves[v]) anyLose |= result[u] == LOSE, allWin &= result[u] == WIN;
            if (anyLose) result[v] = WIN, changed = true;
            else if (allWin) result[v] = LOSE, changed = true;
        }
    }
    return result;
}

int main() {
    auto show = [](const char* name, const vector<vector<int>>& g) {
        auto r = solveGame(g);
        cout << name << ":";
        for (int x : r) cout << " " << "DWL"[x];
        cout << "\n";
    };
    vector<vector<int>> heap(6);  // a heap of 0..5 stones, remove 1 or 2
    for (int x = 1; x <= 5; x++) {
        heap[x].push_back(x - 1);
        if (x >= 2) heap[x].push_back(x - 2);
    }
    show("heap 0..5", heap);
    show("with a cycle", {{1}, {0}, {0, 3}, {}});
    // Check (not printed): 3000 random graphs of up to 7 positions, against the repeated rules.
    mt19937 rng(31);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 7 + 1;
        vector<vector<int>> g(n);
        for (int v = 0; v < n; v++)
            for (int u = 0; u < n; u++)
                if (rng() % 100 < 25) g[v].push_back(u);
        if (solveGame(g) != bruteGame(g)) return 1;
    }
}
