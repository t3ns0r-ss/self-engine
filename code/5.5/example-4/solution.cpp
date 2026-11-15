#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Problem (Codeforces 551E, GukiZ and GukiZiana): n numbers; q operations: "1 l r x" adds x to a_l..a_r, "2 y" asks for the largest j - i
with a_i = a_j = y, or -1 if y does not occur.
Input: n q, the n numbers, then q operations (1-based).
Output: one line per operation of the second kind.
*/

// snippet:begin
// Blocks of B positions: a sorted copy of each block's values and one pending add per block. Whole blocks of a range get the add as a
// note; the ragged ends change one by one and their block's sorted copy is rebuilt.
struct AddBlocks {
    int n, B;
    vector<ll> a, note;
    vector<vector<ll>> sorted;
    AddBlocks(const vector<ll>& v, int block) : n(v.size()), B(block), a(v), note((v.size() + block - 1) / block, 0), sorted(note.size()) {
        for (int b = 0; b < (int)note.size(); b++) rebuild(b);
    }
    void rebuild(int b) {
        sorted[b].assign(a.begin() + b * B, a.begin() + min(n, (b + 1) * B));
        sort(sorted[b].begin(), sorted[b].end());
    }
    void add(int l, int r, ll x) {
        for (int i = l; i <= r;) {
            int b = i / B, last = min(n, (b + 1) * B) - 1;
            if (i == b * B && last <= r) note[b] += x, i = last + 1;
            else {
                for (; i <= min(r, last); i++) a[i] += x;
                rebuild(b);
            }
        }
    }
    int position(int b, ll y, bool fromLeft) const {  // a position in block b holding y, the leftmost or the rightmost; -1 if none
        if (!binary_search(sorted[b].begin(), sorted[b].end(), y - note[b])) return -1;
        int lo = b * B, hi = min(n, (b + 1) * B) - 1;
        for (int i = fromLeft ? lo : hi; lo <= i && i <= hi; i += fromLeft ? 1 : -1)
            if (a[i] + note[b] == y) return i;
        return -1;
    }
    int farthest(ll y) const {  // the largest j - i with a_i = a_j = y, or -1
        int first = -1, last = -1, blocks = note.size();
        for (int b = 0; b < blocks && first < 0; b++) first = position(b, y, true);
        for (int b = blocks - 1; b >= 0 && last < 0; b--) last = position(b, y, false);
        return first < 0 ? -1 : last - first;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;
    AddBlocks blocks(a, max(1, (int)sqrt((double)n)));
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            blocks.add(l - 1, r - 1, x);
        } else {
            ll y;
            cin >> y;
            cout << blocks.farthest(y) << "\n";
        }
    }
}
