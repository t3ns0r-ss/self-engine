#include <bits/stdc++.h>
using namespace std;

// Do the K operations one by one (the generator keeps K small).
int main() {
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> A(N);
    for (auto& a : A) cin >> a;
    long long X = 0;
    for (long long i = 0; i < K; i++) X += A[X % N];
    cout << X << "\n";
}
