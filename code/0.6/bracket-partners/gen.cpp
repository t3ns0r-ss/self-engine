#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 5);
    string s;
    if (randInt(0, 1)) {  // a nested string: push or close the most recent open bracket
        string open;
        for (int i = 0; i < 2 * n; i++) {
            int left = 2 * n - i;
            if (!open.empty() && ((int)open.size() == left || randInt(0, 1))) {
                char c = open.back();
                open.pop_back();
                s += c == '(' ? ')' : c == '[' ? ']' : '}';
            } else {
                char c = "([{"[randInt(0, 2)];
                open += c;
                s += c;
            }
        }
        if (randInt(0, 3) == 0) s[randInt(0, 2 * n - 1)] = "()[]{}"[randInt(0, 5)];  // sometimes break it
    } else {
        for (int i = 0; i < 2 * n; i++) s += "()[]{}"[randInt(0, 5)];
    }
    cout << s << "\n";
}
