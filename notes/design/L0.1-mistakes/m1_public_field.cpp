#include <cstdio>

struct Money {                         // MISTAKE: the field is public, so any code can write any value
    long long cents;
};

void refund(Money& m, long long amount) { m.cents -= amount; }   // nobody checked the balance

int main() {
    Money balance{500};
    refund(balance, 800);
    std::printf("balance = %lld cents\n", balance.cents);        // the rule "never negative" is gone
    return balance.cents < 0 ? 1 : 0;
}
