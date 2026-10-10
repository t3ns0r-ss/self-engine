#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.5.2. The items of the subset that the bits of mask stand for, and the mask of its complement.
vector<int> itemsOf(int mask, int n) {
    vector<int> items;
    for (int i = 0; i < n; i++)
        if ((mask >> i) & 1) items.push_back(i);
    return items;
}
int complement(int mask, int n) { return ((1 << n) - 1) ^ mask; }
// snippet:end

int main() {
    for (int mask : {5, 0}) {
        cout << "n = 3, mask " << mask << ": items";
        for (int i : itemsOf(mask, 3)) cout << ' ' << i;
        cout << "; complement mask " << complement(mask, 3) << ": items";
        for (int i : itemsOf(complement(mask, 3), 3)) cout << ' ' << i;
        cout << '\n';
    }
    for (int n = 0; n <= 10; n++) {  // every subset appears once, and a subset with its complement is all items
        set<vector<int>> seen;
        for (int mask = 0; mask < (1 << n); mask++) {
            seen.insert(itemsOf(mask, n));
            vector<int> both = itemsOf(mask, n), other = itemsOf(complement(mask, n), n);
            both.insert(both.end(), other.begin(), other.end());
            sort(both.begin(), both.end());
            for (int i = 0; i < n; i++)
                if (both[i] != i) return 1;
            if ((int)both.size() != n) return 1;
        }
        if ((int)seen.size() != (1 << n)) return 1;
    }
}
