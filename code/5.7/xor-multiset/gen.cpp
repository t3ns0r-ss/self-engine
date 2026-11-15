#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int q = randInt(1, 12), top = randInt(1, 20);
    multiset<int> present = {0};
    printf("%d\n", q);
    for (int i = 0; i < q; i++) {
        int kind = randInt(0, 2);
        vector<int> removable;
        for (int y : present) removable.push_back(y);
        if (kind == 1 && removable.size() > 1) {  // never remove the last number: a question must have an answer
            int y = removable[randInt(0, removable.size() - 1)];
            present.erase(present.find(y));
            printf("- %d\n", y);
        } else if (kind == 2 || kind == 1) {
            printf("? %d\n", randInt(0, top));
        } else {
            int y = randInt(0, top);
            present.insert(y);
            printf("+ %d\n", y);
        }
    }
}
