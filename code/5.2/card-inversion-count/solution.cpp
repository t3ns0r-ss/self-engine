#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int i, long long d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    }
    long long prefix(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
};

long long inversionsWithTree(const vector<int>& a) {
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    Fenwick f(sorted.size());
    long long total = 0;
    for (int j = 0; j < (int)a.size(); j++) {
        int rank = lower_bound(sorted.begin(), sorted.end(), a[j]) - sorted.begin() + 1;
        total += j - f.prefix(rank);
        f.add(rank, 1);
    }
    return total;
}

int main() {
    // P1 and P2: inversions of 2 4 1 3 5 and of 2 2 1.
    for (auto a : vector<vector<int>>{{2, 4, 1, 3, 5}, {2, 2, 1}}) {
        long long brute = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) brute += a[i] > a[j];
        static int idx = 0;
        cout << "P" << ++idx << " brute=" << brute << " method=" << inversionsWithTree(a) << "\n";
    }
    // N1: pairs i < j with a_i dividing a_j in 2 4 6 3, against the count of earlier elements with a_i <= a_j.
    {
        vector<int> a = {2, 4, 6, 3};
        int brute = 0, method = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) {
                brute += a[j] % a[i] == 0;
                method += a[i] <= a[j];
            }
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
