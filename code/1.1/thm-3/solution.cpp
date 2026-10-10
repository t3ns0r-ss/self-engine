#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.3. The largest number made by joining the given numbers: "x before y when xy > yx" compares
// a key, so it is a valid ordering for sort.
string largestConcat(vector<string> s) {
    sort(s.begin(), s.end(), [](const string& x, const string& y) { return x + y > y + x; });
    string result;
    for (auto& x : s) result += x;
    return result;
}
// snippet:end

int main() {
    for (vector<string> s : {vector<string>{"3", "30", "34", "5", "9"}, vector<string>{"10", "2"}, vector<string>{"1", "1"}}) {
        for (auto& x : s) cout << x << ' ';
        cout << "-> " << largestConcat(s) << '\n';
    }
    mt19937 rng(9);
    for (int round = 0; round < 300; round++) {  // against trying every order
        int n = rng() % 5 + 1;
        vector<string> s(n);
        for (auto& x : s) x = to_string(rng() % 120);
        vector<string> t = s;
        sort(t.begin(), t.end());
        string best;
        do {
            string c;
            for (auto& x : t) c += x;
            if (c.size() > best.size() || (c.size() == best.size() && c > best)) best = c;
        } while (next_permutation(t.begin(), t.end()));
        if (largestConcat(s) != best) return 1;
    }
}
