#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.6.2. Sum of the minimum of every subarray.
long long sumOfMinima(const vector<int>& a) {
    int n = a.size();
    vector<int> L(n), R(n), st;  // L: previous strictly smaller (or -1); R: next smaller-or-equal (or n)
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long total = 0;
    for (int i = 0; i < n; i++) total += (long long)a[i] * (i - L[i]) * (R[i] - i);
    return total;
}
// snippet:end

long long brute(const vector<int>& a) {
    long long sum = 0;
    for (int l = 0; l < (int)a.size(); l++)
        for (int r = l, m = INT_MAX; r < (int)a.size(); r++) sum += m = min(m, a[r]);
    return sum;
}

int main() {
    for (vector<int> a : {vector<int>{3, 1, 2}, {2, 2}, {1, 2, 3}}) {
        cout << "a =";
        for (int x : a) cout << ' ' << x;
        cout << ": sum of minima " << sumOfMinima(a) << '\n';
    }
    vector<int> b(5);  // every array of length 5 over {1, 2, 3}
    for (int code = 0; code < 243; code++) {
        for (int i = 0, c = code; i < 5; i++, c /= 3) b[i] = c % 3 + 1;
        if (sumOfMinima(b) != brute(b)) return 1;
    }
}
