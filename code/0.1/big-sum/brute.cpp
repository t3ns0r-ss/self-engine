// Adds the numbers as decimal strings, digit by digit, so no integer type can overflow.
#include <bits/stdc++.h>
using namespace std;

// |x| + |y| for non-negative decimal strings
string addAbs(const string& x, const string& y) {
    string r;
    int i = x.size() - 1, j = y.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int d = carry + (i >= 0 ? x[i--] - '0' : 0) + (j >= 0 ? y[j--] - '0' : 0);
        r += char('0' + d % 10);
        carry = d / 10;
    }
    reverse(r.begin(), r.end());
    return r;
}
bool lessAbs(const string& x, const string& y) {
    return x.size() != y.size() ? x.size() < y.size() : x < y;
}
// x - y for non-negative strings with x >= y
string subAbs(const string& x, const string& y) {
    string r;
    int i = x.size() - 1, j = y.size() - 1, borrow = 0;
    while (i >= 0) {
        int d = (x[i--] - '0') - borrow - (j >= 0 ? y[j--] - '0' : 0);
        borrow = d < 0;
        r += char('0' + (d + 10) % 10);
    }
    while (r.size() > 1 && r.back() == '0') r.pop_back();
    reverse(r.begin(), r.end());
    return r;
}

int main() {
    int n;
    cin >> n;
    bool neg = false;
    string mag = "0";  // the sum is (neg ? -mag : mag)
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        bool sneg = s[0] == '-';
        string sm = sneg ? s.substr(1) : s;
        if (neg == sneg) {
            mag = addAbs(mag, sm);
        } else if (lessAbs(mag, sm)) {
            mag = subAbs(sm, mag);
            neg = sneg;
        } else {
            mag = subAbs(mag, sm);
        }
        if (mag == "0") neg = false;
    }
    cout << (neg ? "-" : "") << mag << "\n";
}
