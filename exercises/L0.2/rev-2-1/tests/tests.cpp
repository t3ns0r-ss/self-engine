#include <memory>
#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "pipeline.hpp"

static_assert(std::is_abstract_v<Step>);
static_assert(std::has_virtual_destructor_v<Step>);

static int live = 0;
struct Probe final : Step {
    Probe() { ++live; }
    ~Probe() override { --live; }
    long long apply(long long x) const override { return x - 1; }
};

void the_steps_apply_in_order() {
    Pipeline p;
    p.add(std::make_unique<AddStep>(2));
    p.add(std::make_unique<MulStep>(5));
    CHECK(p.size() == 2);
    CHECK(p.run(1) == 15);                         // (1 + 2) * 5
}
void the_order_matters() {
    Pipeline p;
    p.add(std::make_unique<MulStep>(5));
    p.add(std::make_unique<AddStep>(2));
    CHECK(p.run(1) == 7);                          // 1 * 5 + 2
}
void an_empty_pipeline_returns_its_input() {
    Pipeline p;
    CHECK(p.size() == 0);
    CHECK(p.run(42) == 42);
}
void a_null_step_is_refused() {
    Pipeline p;
    CHECK_THROWS(p.add(nullptr));
    CHECK(p.size() == 0);
}
void a_step_from_the_caller_works_and_is_destroyed_with_the_pipeline() {
    CHECK(live == 0);
    {
        Pipeline p;
        p.add(std::make_unique<Probe>());
        p.add(std::make_unique<Probe>());
        CHECK(live == 2);
        CHECK(p.run(10) == 8);
    }
    CHECK(live == 0);
}
void the_steps_are_separate_objects() {
    AddStep a(1);
    MulStep m(3);
    const Step& sa = a;
    const Step& sm = m;
    CHECK(sa.apply(10) == 11);
    CHECK(sm.apply(10) == 30);
}

int main() {
    RUN(the_steps_apply_in_order);
    RUN(the_order_matters);
    RUN(an_empty_pipeline_returns_its_input);
    RUN(a_null_step_is_refused);
    RUN(a_step_from_the_caller_works_and_is_destroyed_with_the_pipeline);
    RUN(the_steps_are_separate_objects);
    return check::report();
}
