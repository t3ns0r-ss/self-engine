#include <bits/stdc++.h>
using namespace std;

const long long NONE = LLONG_MIN;  // "there is no other number"

// snippet:begin
// Theorem 7.10.2. For every position i, the largest of all the other numbers (NONE if there is no other).
// Two best values: b1 is the largest at position where, b2 is the second largest (a tie counts as a second value).
vector<long long> maxWithout(const vector<long long>& a) {
    long long b1 = NONE, b2 = NONE;
    int where = -1;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] > b1) b2 = b1, b1 = a[i], where = i;
        else b2 = max(b2, a[i]);
    }
    vector<long long> out(a.size());
    for (int i = 0; i < (int)a.size(); i++) out[i] = (i == where ? b2 : b1);
    return out;
}

// The same with prefix and suffix maxima: it works for any combination, not only a maximum.
vector<long long> maxWithoutPrefix(const vector<long long>& a) {
    int k = a.size();
    vector<long long> suffix(k + 1, NONE), out(k);
    for (int i = k - 1; i >= 0; i--) suffix[i] = max(suffix[i + 1], a[i]);
    long long prefix = NONE;
    for (int i = 0; i < k; i++) out[i] = max(prefix, suffix[i + 1]), prefix = max(prefix, a[i]);
    return out;
}
// snippet:end

void show(const vector<long long>& a) {
    cout << "[";
    for (size_t i = 0; i < a.size(); i++) cout << (i ? ", " : "") << a[i];
    cout << "] ->";
    for (long long x : maxWithout(a)) {
        if (x == NONE) cout << " none";
        else cout << " " << x;
    }
    cout << "\n";
}

int main() {
    show({3, 7, 7, 2});
    show({5, 1, 4});
    show({6});
    // Check (not printed): both functions equal the direct answer for every list of length 1 to 5 over the values 0..3.
    for (int k = 1; k <= 5; k++) {
        int total = 1;
        for (int i = 0; i < k; i++) total *= 4;
        for (int code = 0; code < total; code++) {
            vector<long long> a(k);
            for (int i = 0, c = code; i < k; i++, c /= 4) a[i] = c % 4;
            vector<long long> one = maxWithout(a), two = maxWithoutPrefix(a);
            for (int i = 0; i < k; i++) {
                long long want = NONE;
                for (int j = 0; j < k; j++)
                    if (j != i) want = max(want, a[j]);
                if (one[i] != want || two[i] != want) return 1;
            }
        }
    }
}
