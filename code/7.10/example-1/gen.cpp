#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int H = randInt(1, 5), W = randInt(1, 5);
    vector<pair<int, int>> cells;
    for (int r = 1; r <= H; r++)
        for (int c = 1; c <= W; c++) cells.push_back({r, c});
    shuffle(cells.begin(), cells.end(), rng);
    int M = randInt(1, (int)cells.size());
    printf("%d %d %d\n", H, W, M);
    for (int i = 0; i < M; i++) printf("%d %d\n", cells[i].first, cells[i].second);
}
