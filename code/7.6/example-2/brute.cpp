#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums;
map<int, bool> memo;
bool win(int removed) {  // the player to move wins? removed = the set of erased positions
    auto it = memo.find(removed);
    if (it != memo.end()) return it->second;
    int x = 0, left = 0;
    for (int i = 0; i < n; i++)
        if (!(removed >> i & 1)) x ^= nums[i], left++;
    bool result;
    if (x == 0) result = true;  // the xor is 0 at the start of the turn
    else {
        result = false;
        for (int i = 0; i < n && !result; i++)
            if (!(removed >> i & 1) && (x ^ nums[i]) != 0 && !win(removed | 1 << i)) result = true;  // erasing must not make the xor 0
    }
    return memo[removed] = result;
}
int main() {
    cin >> n;
    nums.resize(n);
    for (int& v : nums) cin >> v;
    cout << (win(0) ? "true" : "false") << "\n";
}
