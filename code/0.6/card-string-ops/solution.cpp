#include <bits/stdc++.h>
using namespace std;

// Letters left after removing the leftmost ABC again and again (find and erase), and with a string used as a stack.
static int bruteTake(string s) {
    size_t p;
    while ((p = s.find("ABC")) != string::npos) s.erase(p, 3);
    return (int)s.size();
}
static int stackTake(const string& s) {
    string t;
    for (char c : s) {
        t += c;
        int m = t.size();
        if (m >= 3 && t.compare(m - 3, 3, "ABC") == 0) t.resize(m - 3);
    }
    return (int)t.size();
}

int main() {
    // P1: how many letters are left of "AABCBC" after removing ABC again and again?
    cout << "P1 brute=" << bruteTake("AABCBC") << " method=" << stackTake("AABCBC") << '\n';
    // N1: how many times does "aa" appear in "aaaa"? Brute: test every start. Method: find that resumes after each match.
    string s = "aaaa", t = "aa";
    int brute = 0;
    for (size_t i = 0; i + t.size() <= s.size(); i++) brute += s.compare(i, t.size(), t) == 0;
    int method = 0;
    for (size_t p = s.find(t); p != string::npos; p = s.find(t, p + t.size())) method++;
    cout << "N1 brute=" << brute << " method=" << method << '\n';
    // N2: is 10 smaller than 9? Brute: compare the numbers. Method: compare the texts "10" and "9".
    cout << "N2 brute=" << (stoi("10") < stoi("9") ? "yes" : "no") << " method=" << (string("10") < string("9") ? "yes" : "no") << '\n';
}
