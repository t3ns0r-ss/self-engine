#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;
struct BinaryTrie {
    vector<array<int, 2>> child = {{0, 0}};
    vector<int> cnt = {0};
    void add(int x, int delta) {
        int v = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1;
            if (!child[v][d]) {
                child[v][d] = child.size();
                child.push_back({0, 0});
                cnt.push_back(0);
            }
            v = child[v][d];
            cnt[v] += delta;
        }
    }
    int maxXor(int x) const {
        int v = 0, best = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1, opposite = child[v][d ^ 1];
            if (opposite && cnt[opposite] > 0) best |= 1 << b, v = opposite;
            else v = child[v][d];
        }
        return best;
    }
    long long countXorBelow(int x, int k) const {
        long long total = 0;
        int v = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int d = x >> b & 1;
            if (k >> b & 1) {
                if (child[v][d]) total += cnt[child[v][d]];
                v = child[v][d ^ 1];
            } else {
                v = child[v][d];
            }
            if (!v) break;
        }
        return total;
    }
};

int main() {
    {
        vector<int> a = {3, 10, 5, 25, 2, 8};
        int brute = 0, method = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) brute = max(brute, a[i] ^ a[j]);
        BinaryTrie t;
        t.add(a[0], +1);
        for (size_t i = 1; i < a.size(); i++) {
            method = max(method, t.maxXor(a[i]));
            t.add(a[i], +1);
        }
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    {
        vector<int> a = {1, 2, 3, 4};
        long long brute = 0, method = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) brute += (a[i] ^ a[j]) < 3;
        BinaryTrie t;
        for (int x : a) {
            method += t.countXorBelow(x, 3);  // count against the earlier numbers first, then insert
            t.add(x, +1);
        }
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: the largest AND of two numbers; the pair with the largest XOR is not the pair with the largest AND.
        vector<int> a = {5, 6, 3};
        int brute = 0, bestXor = -1, method = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) {
                brute = max(brute, a[i] & a[j]);
                if ((a[i] ^ a[j]) > bestXor) bestXor = a[i] ^ a[j], method = a[i] & a[j];
            }
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
