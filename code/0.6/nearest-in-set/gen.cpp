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
    int q = randInt(1, 15);
    vector<int> have;  // to remove only values that are present
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int type = randInt(1, 4);
        if (type == 2 && have.empty()) type = 1;
        if (type == 1) {
            int x = randInt(0, 10);
            have.push_back(x);
            cout << "1 " << x << "\n";
        } else if (type == 2) {
            int k = randInt(0, (int)have.size() - 1);
            cout << "2 " << have[k] << "\n";
            have.erase(have.begin() + k);
        } else {
            cout << type << " " << randInt(0, 10) << "\n";
        }
    }
}
