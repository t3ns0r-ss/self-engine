#include <bits/stdc++.h>
using namespace std;

/*
Problem: n objects in a circle, numbered 1..n; the object 1 is a black hole. Two players have sets of moves: in a move a player moves the
monster x steps clockwise, for an x in his set. A player who moves the monster into the black hole wins. For every start object 2..n,
and for each of the two players moving first, print Win, Lose or Loop (nobody can force a win).
Input: n, then k1 and the k1 moves of the first player, then k2 and the k2 moves of the second player.
Output: two lines of n - 1 words: the first player moves first, then the second player moves first.
*/

// Theorem 7.5.1 (outside the shown code): the results of all positions of a game graph; DRAW = 0, WIN = 1, LOSE = 2.
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

// snippet:begin
// Theorem 7.5.1 on the states (object, player to move). The black hole with a player to move is LOSE: the other player has just moved in.
// The state (p, who) has the moves to ((p - 1 + x) mod n + 1, the other player) for x in the set of `who`.
vector<int> berzerk(int n, const vector<int> steps[2]) {
    vector<vector<int>> moves(2 * n);  // the state (p, who) has the number 2 * (p - 1) + who
    for (int p = 2; p <= n; p++)
        for (int who = 0; who < 2; who++)
            for (int x : steps[who]) moves[2 * (p - 1) + who].push_back(2 * ((p - 1 + x) % n) + 1 - who);
    return solveGame(moves);
}
// snippet:end

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
    auto result = berzerk(n, steps);
    const char* name[] = {"Loop", "Win", "Lose"};
    for (int first = 0; first < 2; first++)
        for (int p = 2; p <= n; p++) cout << name[result[2 * (p - 1) + first]] << (p < n ? " " : "\n");
}
