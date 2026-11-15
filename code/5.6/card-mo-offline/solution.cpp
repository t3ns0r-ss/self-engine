#include <bits/stdc++.h>
using namespace std;

vector<int> moOrder(const vector<array<int, 2>>& queries, int n) {
    int B = max(1, (int)(n / sqrt((double)max<size_t>(1, queries.size()))));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        int bx = queries[x][0] / B, by = queries[y][0] / B;
        if (bx != by) return bx < by;
        return bx % 2 == 0 ? queries[x][1] < queries[y][1] : queries[x][1] > queries[y][1];
    });
    return order;
}
// Mo's algorithm with a generic window value: add(i) and remove(i) repair `value`.
template <class Add, class Remove>
vector<long long> mo(int n, const vector<array<int, 2>>& queries, Add add, Remove remove, const long long& value) {
    vector<long long> answer(queries.size());
    int l = 0, r = -1;
    for (int q : moOrder(queries, n)) {
        auto [ql, qr] = queries[q];
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) remove(l++);
        while (r > qr) remove(r--);
        answer[q] = value;
    }
    return answer;
}

int main() {
    // P1: a = 1 2 1 3 2 2 4 1; the number of different values in positions 0..3.
    {
        vector<int> a = {1, 2, 1, 3, 2, 2, 4, 1};
        vector<int> cnt(5, 0);
        long long distinct = 0;
        auto got = mo(8, {{0, 3}}, [&](int i) { distinct += cnt[a[i]]++ == 0; }, [&](int i) { distinct -= --cnt[a[i]] == 0; }, distinct);
        cout << "P1 brute=" << set<int>(a.begin(), a.begin() + 4).size() << " method=" << got[0] << "\n";
    }
    // P2: a = 2 1 2 2 1; the sum over the values v of v * count(v)^2 in the whole array.
    {
        vector<int> a = {2, 1, 2, 2, 1};
        vector<int> cnt(3, 0);
        long long power = 0;
        auto got = mo(5, {{0, 4}}, [&](int i) { power += (long long)a[i] * (2 * cnt[a[i]]++ + 1); }, [&](int i) { power -= (long long)a[i] * (2 * --cnt[a[i]] + 1); }, power);
        map<int, int> c;
        for (int x : a) c[x]++;
        long long brute = 0;
        for (auto [v, k] : c) brute += (long long)v * k * k;
        cout << "P2 brute=" << brute << " method=" << got[0] << "\n";
    }
    // N1: a = 1 2 3, then a_3 is set to 1; the number of different values in positions 0..2 is asked.
    // Mo's algorithm works on the array it was given (before the change), so it counts 3.
    {
        vector<int> before = {1, 2, 3}, after = {1, 2, 1};
        vector<int> cnt(4, 0);
        long long distinct = 0;
        auto got = mo(3, {{0, 2}}, [&](int i) { distinct += cnt[before[i]]++ == 0; }, [&](int i) { distinct -= --cnt[before[i]] == 0; }, distinct);
        cout << "N1 brute=" << set<int>(after.begin(), after.end()).size() << " method=" << got[0] << "\n";
    }
}
