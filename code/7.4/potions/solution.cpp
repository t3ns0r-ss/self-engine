#include <bits/stdc++.h>
using namespace std;

/*
Problem: n potions in a row; drinking the i-th changes the health by a_i (possibly negative). The health starts at 0 and must never be
negative. Print the largest number of potions that can be drunk, in the order of the row.
Input: n, then the n numbers a_i.
Output: the largest number.
*/


// snippet:begin
// Theorem 7.4.1 (the balance form): drink every potion in turn; when the health becomes negative, put back the most harmful potion drunk
// so far (the smallest number in the heap). A harmful potion is a course whose last day is the sum of the good potions before it.
int mostPotions(const vector<long long>& a) {
    priority_queue<long long, vector<long long>, greater<long long>> drunk;
    long long health = 0;
    for (long long x : a) {
        drunk.push(x), health += x;
        if (health < 0) health -= drunk.top(), drunk.pop();
    }
    return drunk.size();
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << mostPotions(a) << "\n";
}
