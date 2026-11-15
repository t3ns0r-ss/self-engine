#include <bits/stdc++.h>
using namespace std;

struct StepSums {
    int n, B;
    vector<long long> a;
    vector<vector<long long>> table;
    StepSums(const vector<long long>& v, int threshold) : n(v.size()), B(threshold), a(v), table(threshold) {
        for (int k = 1; k < B; k++) {
            table[k].assign(n + k, 0);
            for (int p = n - 1; p >= 0; p--) table[k][p] = a[p] + table[k][p + k];
        }
    }
    long long query(int p, int k) const {
        if (k < B) return table[k][p];
        long long s = 0;
        for (; p < n; p += k) s += a[p];
        return s;
    }
};
vector<int> exactlyXTimes(const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size();
    vector<int> total(n + 1, 0), answer(queries.size(), 0), prefix(n + 1, 0);
    for (int x : a)
        if (x <= n) total[x]++;
    for (int x = 1; x <= n; x++) {
        if (total[x] < x) continue;
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + (a[i] == x);
        for (size_t j = 0; j < queries.size(); j++) answer[j] += prefix[queries[j][1] + 1] - prefix[queries[j][0]] == x;
    }
    return answer;
}

int main() {
    // P1: a = 3 1 4 1 5 9 2 6 5 3; the step sum from position 1 with step 2.
    {
        vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        StepSums s(a, 3);
        long long brute = 0;
        for (int i = 1; i < 10; i += 2) brute += a[i];
        cout << "P1 brute=" << brute << " method=" << s.query(1, 2) << "\n";
    }
    // P2: a = 3 1 2 2 3 3 1 3; how many values x occur exactly x times in positions 0..4.
    {
        vector<int> a = {3, 1, 2, 2, 3, 3, 1, 3};
        map<int, int> c;
        for (int i = 0; i <= 4; i++) c[a[i]]++;
        int brute = 0;
        for (auto [x, k] : c) brute += x == k;
        cout << "P2 brute=" << brute << " method=" << exactlyXTimes(a, {{0, 4}})[0] << "\n";
    }
    // N1: a = 3 1 4 1 5, the table for step 2 is built, then a_2 is set to 0; the step sum from 0 with step 2 is asked.
    {
        vector<long long> a = {3, 1, 4, 1, 5};
        StepSums s(a, 3);
        a[2] = 0;
        long long brute = 0;
        for (int i = 0; i < 5; i += 2) brute += a[i];
        cout << "N1 brute=" << brute << " method=" << s.query(0, 2) << "\n";
    }
}
