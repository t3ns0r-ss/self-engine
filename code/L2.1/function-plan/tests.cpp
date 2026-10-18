#include "check.hpp"
#include "fee_book.hpp"

long long flat_ten(long long) { return 10; }                       // a plain function

struct PerHour {                                                    // an object with operator()
    long long rate;
    long long operator()(long long minutes) const { return (minutes + 59) / 60 * rate; }
};

void lambda_plan() {
    FeeBook book;
    book.add("HOURLY", [](long long m) { return (m + 59) / 60 * 20; });
    CHECK(book.fee("HOURLY", 61) == 40);
}
void plain_function_plan() {
    FeeBook book;
    book.add("FLAT", flat_ten);
    CHECK(book.fee("FLAT", 500) == 10);
}
void object_plan_with_state() {
    FeeBook book;
    book.add("WEEKEND", PerHour{40});
    CHECK(book.fee("WEEKEND", 61) == 80);
}
void lambda_captures_a_copy_of_its_setting() {
    FeeBook book;
    long long rate = 20;
    book.add("HOURLY", [rate](long long m) { return (m + 59) / 60 * rate; });
    rate = 999;   // changing the variable afterwards does not change the stored plan
    CHECK(book.fee("HOURLY", 60) == 20);
}
void unknown_plan_throws() {
    FeeBook book;
    CHECK_THROWS(book.fee("NOPE", 10));
}
void empty_function_is_rejected_when_added() {
    FeeBook book;
    CHECK_THROWS(book.add("BAD", FeeFn{}));
}
void adding_a_plan_again_replaces_it() {
    FeeBook book;
    book.add("P", [](long long) { return 1LL; });
    book.add("P", [](long long) { return 2LL; });
    CHECK(book.fee("P", 0) == 2);
}

int main() {
    RUN(lambda_plan);
    RUN(plain_function_plan);
    RUN(object_plan_with_state);
    RUN(lambda_captures_a_copy_of_its_setting);
    RUN(unknown_plan_throws);
    RUN(empty_function_is_rejected_when_added);
    RUN(adding_a_plan_again_replaces_it);
    return check::report();
}
