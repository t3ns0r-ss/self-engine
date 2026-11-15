#include <bits/stdc++.h>
using namespace std;

int main() {
    long long L, A, B, M;
    cin >> L >> A >> B >> M;
    long long x = 0;
    for (long long i = 0; i < L; i++) {
        string digits = to_string(A + B * i);
        for (char ch : digits) x = (x * 10 + (ch - '0')) % M;
    }
    cout << x << "\n";
}
