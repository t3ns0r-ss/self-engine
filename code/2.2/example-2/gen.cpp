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
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    shuffle(primes.begin(), primes.end(), rng);
    vector<pair<int, int>> f;
    long long N = 1;
    for (int p : primes) {  // keep N <= 10^5 so the brute force can list the divisors
        int k = randInt(0, 6);
        long long v = N;
        int used = 0;
        for (int j = 0; j < k && v * p <= 100000; j++) v *= p, used++;
        if (used > 0) f.push_back({p, used}), N = v;
    }
    if (f.empty()) f.push_back({2, 1});
    cout << f.size() << "\n";
    for (auto [p, k] : f) cout << p << " " << k << "\n";
}
