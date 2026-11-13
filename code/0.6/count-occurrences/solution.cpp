/*
Problem: how many times does the string T appear in the string S as a consecutive piece? Pieces may
overlap: "aa" appears 3 times in "aaaa".
Input: S, then T (1 <= |T| <= |S| <= 1000).
Output: the number of appearances.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Count the places where t starts inside s. find returns string::npos when there is no match.
int countOccurrences(const string& s, const string& t) {
    int count = 0;
    size_t pos = s.find(t);
    while (pos != string::npos) {
        count++;
        pos = s.find(t, pos + 1);  // + 1, not + t.size(): overlapping matches count
    }
    return count;
}
// snippet:end

int main() {
    string s, t;
    cin >> s >> t;
    cout << countOccurrences(s, t) << "\n";
}
