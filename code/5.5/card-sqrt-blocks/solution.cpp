#include <bits/stdc++.h>
using namespace std;

struct Blocks {
    int n, B;
    vector<long long> a, sum, add;
    Blocks(const vector<long long>& v, int block) : n(v.size()), B(block), a(v), sum((v.size() + block - 1) / block, 0), add(sum) {
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }
    int end(int b) const { return min(n, (b + 1) * B) - 1; }
    void addRange(int l, int r, long long x) {
        for (int i = l; i <= r;) {
            int b = i / B;
            if (i == b * B && end(b) <= r) add[b] += x, sum[b] += x * (end(b) - i + 1), i = end(b) + 1;
            else a[i] += x, sum[b] += x, i++;
        }
    }
    long long rangeSum(int l, int r) const {
        long long s = 0;
        for (int i = l; i <= r;) {
            int b = i / B;
            if (i == b * B && end(b) <= r) s += sum[b], i = end(b) + 1;
            else s += a[i] + add[b], i++;
        }
        return s;
    }
};
struct SortedBlocks {
    int n, B;
    vector<int> a;
    vector<vector<int>> sorted;
    SortedBlocks(const vector<int>& v, int block) : n(v.size()), B(block), a(v), sorted((v.size() + block - 1) / block) {
        for (int i = 0; i < n; i++) sorted[i / B].push_back(a[i]);
        for (auto& s : sorted) sort(s.begin(), s.end());
    }
    int countLess(int l, int r, int x) const {
        int cnt = 0;
        for (int i = l; i <= r;) {
            int b = i / B, last = min(n, (b + 1) * B) - 1;
            if (i == b * B && last <= r) cnt += lower_bound(sorted[b].begin(), sorted[b].end(), x) - sorted[b].begin(), i = last + 1;
            else cnt += a[i] < x, i++;
        }
        return cnt;
    }
};

int main() {
    // P1: a = 3 1 4 1 5 9 2 6 5 3, B = 3; add 10 to positions 2..8; sum of positions 1..9.
    {
        vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        Blocks b(a, 3);
        b.addRange(2, 8, 10);
        for (int i = 2; i <= 8; i++) a[i] += 10;
        long long brute = 0;
        for (int i = 1; i <= 9; i++) brute += a[i];
        cout << "P1 brute=" << brute << " method=" << b.rangeSum(1, 9) << "\n";
    }
    // P2: a = 5 2 8 1 9 3 7 4 6, B = 3; how many values below 5 in positions 1..7.
    {
        vector<int> a = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        SortedBlocks s(a, 3);
        int brute = 0;
        for (int i = 1; i <= 7; i++) brute += a[i] < 5;
        cout << "P2 brute=" << brute << " method=" << s.countLess(1, 7, 5) << "\n";
    }
    // N1: the most frequent value of a range, answered as the most frequent among the modes of the blocks (ties: smallest).
    {
        vector<int> a = {1, 2, 3, 2, 4, 5, 2, 6, 7, 1, 8, 9};
        map<int, int> all;
        for (int x : a) all[x]++;
        int brute = 0, bestCount = 0;
        for (auto [v, c] : all)
            if (c > bestCount) bestCount = c, brute = v;
        map<int, int> modes;
        for (int b = 0; b < 4; b++) {
            map<int, int> c;
            for (int i = 3 * b; i < 3 * b + 3; i++) c[a[i]]++;
            int mode = 0, best = 0;
            for (auto [v, k] : c)
                if (k > best) best = k, mode = v;
            modes[mode]++;
        }
        int method = 0;
        bestCount = 0;
        for (auto [v, c] : modes)
            if (c > bestCount) bestCount = c, method = v;
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
