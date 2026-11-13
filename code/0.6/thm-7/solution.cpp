#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.7. Characters written when a string of length n is built one letter at a time.
long long writesPlusEq(int n) {  // s += c: the buffer doubles when it is full
    long long writes = 0, capacity = 1, size = 0;
    for (int i = 0; i < n; i++) {
        if (size == capacity) {  // full: copy the old text into twice the space
            writes += size;
            capacity *= 2;
        }
        writes++;  // the new letter
        size++;
    }
    return writes;
}

long long writesPlusAssign(int n) {  // s = s + c: call i builds a new string of i letters
    long long writes = 0;
    for (int i = 1; i <= n; i++) writes += i;
    return writes;
}

// Characters touched when every window of length m of a text of length n is cut out and compared.
long long windowCost(int n, int m) { return 1LL * (n - m + 1) * m; }
// snippet:end

// Counts the letters copied while n letters are appended to a real string with +=.
static long long realCopies(int n) {
    string s;
    long long copies = 0;
    for (int i = 0; i < n; i++) {
        const char* before = s.data();
        size_t size = s.size();
        s += 'x';
        if (s.data() != before) copies += (long long)size;  // the buffer moved: the old text was copied
    }
    return copies;
}

int main() {
    for (int n : {5, 1000}) cout << "n=" << n << " plus_eq=" << writesPlusEq(n) << " plus_assign=" << writesPlusAssign(n) << '\n';
    string s = "abcdef";
    cout << "substr(2,3)=" << s.substr(2, 3) << " writes 3\n";
    cout << "windows n=6 m=3: " << 6 - 3 + 1 << " windows, " << windowCost(6, 3) << " character steps\n";
    for (int n = 1; n <= 3000; n++) {
        if (writesPlusEq(n) >= 3LL * n) return 1;  // fewer than 3n writes in all
        if (writesPlusAssign(n) != 1LL * n * (n + 1) / 2) return 1;
        if (realCopies(n) >= 2LL * n) return 1;  // the real string copies fewer than 2n letters
    }
    // A window loop written out by hand does exactly windowCost steps.
    for (int n = 1; n <= 12; n++)
        for (int m = 1; m <= n; m++) {
            long long steps = 0;
            for (int i = 0; i + m <= n; i++)
                for (int j = 0; j < m; j++) steps++;
            if (steps != windowCost(n, m)) return 1;
        }
    // substr copies min(k, n - i) letters.
    if (s.substr(4, 10) != "ef" || !s.substr(6).empty()) return 1;
    // find returns npos, the largest size_t, when there is no match.
    if (string("abc").find("d") != string::npos || string::npos != (size_t)-1) return 1;
    // stoi throws when the number does not fit in an int; stoll holds it.
    bool threw = false;
    try {
        stoi("2147483648");
    } catch (const out_of_range&) {
        threw = true;
    }
    if (!threw || stoll("2147483648") != 2147483648LL) return 1;
    // Strings compare letter by letter, not as numbers.
    if (!(string("10") < string("9")) || stoi("10") < stoi("9")) return 1;
    // An array of 26 counters decides anagrams.
    auto anagram = [](const string& a, const string& b) {
        int cnt[26] = {};
        for (char c : a) cnt[c - 'a']++;
        for (char c : b) cnt[c - 'a']--;
        for (int x : cnt)
            if (x != 0) return false;
        return true;
    };
    if (!anagram("listen", "silent") || anagram("rat", "car")) return 1;
    return 0;
}
