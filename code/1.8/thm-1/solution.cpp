#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.8.1. The fewest yes/no questions that always find one of n numbers: the smallest q with 2^q >= n.
int fewestQuestions(int n) {
    int q = 0;
    while ((1 << q) < n) q++;
    return q;
}

// Halving: the hidden x is in 1..n. Ask "x <= mid?" and keep the half that agrees. Returns the number of questions.
int halve(int n, int x, int& found) {
    int lo = 0, hi = n, asked = 0;  // "x <= lo" is false and "x <= hi" is true, by agreement
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        asked++;
        if (x <= mid) hi = mid;
        else lo = mid;
    }
    found = hi;
    return asked;
}
// snippet:end

// The best worst case over every possible strategy, found by trying every question (every subset of the still possible
// numbers is a question "is x in this subset?"). best[S] = fewest questions that always decide among the numbers in S.
int bestWorstCase(int n) {
    vector<int> best(1 << n, 0);
    for (int s = 1; s < (1 << n); s++) {
        if (__builtin_popcount(s) <= 1) continue;
        best[s] = INT_MAX;
        for (int t = (s - 1) & s; t > 0; t = (t - 1) & s)  // every non-empty proper subset t of s
            best[s] = min(best[s], 1 + max(best[t], best[s ^ t]));
    }
    return best[(1 << n) - 1];
}

int main() {
    // The examples shown in the lesson.
    for (int n : {8, 10, 1}) {
        int worst = 0;
        for (int x = 1; x <= n; x++) {
            int found;
            worst = max(worst, halve(n, x, found));
        }
        cout << "n = " << n << ": at least " << fewestQuestions(n) << " questions; halving needs at most " << worst << "\n";
    }
    {
        int found;
        int asked = halve(5, 4, found);
        cout << "n = 5, x = 4: halving asks about 2, 3 and 4, finds " << found << " in " << asked << " questions\n";
    }
    // The check: halving never needs more than the bound and is right; no strategy does better (n up to 12).
    for (int n = 1; n <= 200; n++)
        for (int x = 1; x <= n; x++) {
            int found;
            if (halve(n, x, found) > fewestQuestions(n) || found != x) return 1;
        }
    for (int n = 1; n <= 12; n++)
        if (bestWorstCase(n) != fewestQuestions(n)) return 1;
    return 0;
}
