#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    cout << (atoi(argv[1]) % 38) + 1 << "\n";  // every K from 1 to 38
}
