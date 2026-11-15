#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.8.4. An adaptive judge for "x <= m?": it has no number in mind. It keeps the numbers lo..hi that still
// agree with every reply, and answers so that the larger group stays possible (a tie: no). Some number always agrees.
struct AdaptiveJudge {
    int lo, hi;
    explicit AdaptiveJudge(int n) : lo(1), hi(n) {}
    bool atMost(int m) {
        int yes = max(0, min(hi, m) - lo + 1);     // numbers that agree with the reply "yes"
        int no = max(0, hi - max(lo, m + 1) + 1);  // numbers that agree with the reply "no"
        bool reply = yes > no;
        if (reply) hi = min(hi, m);
        else lo = max(lo, m + 1);
        return reply;
    }
};
// snippet:end

// The strategy of Theorem 1.4.1: halving. It sees only the replies.
template <class Ask>
int halving(int n, Ask ask, vector<int>& questions) {
    int lo = 0, hi = n;
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        questions.push_back(mid);
        if (ask(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

// Every sequence of replies that obeys the consistency rule, found by trying both replies whenever both keep a number
// possible. At each end of a play: halving finished within the bound, exactly one number agrees with the replies and
// it is the answer of halving, and a judge with that number fixed gives the same questions and replies.
struct NeedReply {
    int question;
};

struct Checker {
    int n, bound, leaves = 0;
    bool ok = true;

    void explore(vector<bool>& replies) {
        int agreeLo = 1, agreeHi = n, step = 0;
        vector<int> questions;
        int found = -1;
        try {
            found = halving(n, [&](int m) -> bool {
                if (step == (int)replies.size()) throw NeedReply{m};
                bool reply = replies[step++];
                if (reply) agreeHi = min(agreeHi, m);
                else agreeLo = max(agreeLo, m + 1);
                return reply;
            }, questions);
        } catch (const NeedReply& need) {
            int m = need.question;
            int yes = max(0, min(agreeHi, m) - agreeLo + 1), no = max(0, agreeHi - max(agreeLo, m + 1) + 1);
            for (bool reply : {false, true}) {
                if ((reply ? yes : no) == 0) continue;  // this reply would leave no number: not allowed
                replies.push_back(reply);
                explore(replies);
                replies.pop_back();
            }
            return;
        }
        leaves++;
        vector<int> again;
        int fixedFound = halving(n, [&](int m) { return agreeLo <= m; }, again);  // a judge with that number fixed
        if ((int)questions.size() > bound || agreeLo != agreeHi || found != agreeLo || fixedFound != found || again != questions)
            ok = false;
    }
};

bool checkAll(int n, int bound) {
    Checker checker{n, bound};
    vector<bool> replies;
    checker.explore(replies);
    return checker.ok && checker.leaves == n;  // one end of a play for each number
}

int main() {
    for (int n : {8, 5, 1}) {
        AdaptiveJudge judge(n);
        vector<int> questions;
        string replies;
        int found = halving(n, [&](int m) {
            bool r = judge.atMost(m);
            replies += r ? " yes" : " no";
            return r;
        }, questions);
        cout << "n = " << n << ": the replies" << (replies.empty() ? " (none)" : replies) << ", found " << found << " after "
             << questions.size() << " questions\n";
    }
    for (int n = 1; n <= 24; n++) {
        int bound = 0;
        while ((1 << bound) < n) bound++;
        if (!checkAll(n, bound)) return 1;
    }
    return 0;
}
