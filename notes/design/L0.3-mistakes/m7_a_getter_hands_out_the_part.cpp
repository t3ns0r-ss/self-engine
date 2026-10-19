#include <cstdio>
#include <stdexcept>
#include <vector>

struct Line { int quantity; int price_cents; };

class Order {
public:
    void add(int quantity, int price_cents) {
        if (quantity <= 0 || price_cents < 0) throw std::invalid_argument("bad line");   // the rule: every line is valid
        lines_.push_back(Line{quantity, price_cents});
    }
    std::vector<Line>& lines() { return lines_; }  // MISTAKE: hands out the part, so the rule can be skipped
    long long total_cents() const {
        long long t = 0;
        for (const Line& l : lines_) t += static_cast<long long>(l.quantity) * l.price_cents;
        return t;
    }
private:
    std::vector<Line> lines_;
};

int main() {
    Order o;
    o.add(2, 500);
    o.lines().push_back(Line{-3, 500});            // compiles; skips the check in add
    std::printf("total = %lld (expected 1000 or a refused line)\n", o.total_cents());
    return o.total_cents() >= 0 ? 0 : 1;
}
