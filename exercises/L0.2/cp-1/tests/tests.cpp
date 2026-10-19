#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "service.hpp"

static_assert(std::is_abstract_v<Shape>);
static_assert(std::has_virtual_destructor_v<Shape>);
static_assert(!HasArea<int>);

static int live = 0;
struct Probe final : Shape {                    // a shape the service has never heard of
    explicit Probe(long long a) : a_(a) { ++live; }
    ~Probe() override { --live; }
    long long area() const override { return a_; }
    long long perimeter() const override { return 0; }
    std::string name() const override { return "probe"; }
    long long a_;
};

void the_shapes_answer_for_themselves() {
    Rect r(3, 4);
    Square s(5);
    CHECK(r.area() == 12);
    CHECK(r.perimeter() == 14);
    CHECK(r.name() == "rect");
    CHECK(s.area() == 25);
    CHECK(s.perimeter() == 20);
    CHECK(s.name() == "square");
}
void the_service_totals_a_mixed_list() {
    AreaService svc;
    svc.add(std::make_unique<Rect>(3, 4));
    svc.add(std::make_unique<Square>(5));
    CHECK(svc.count() == 2);
    CHECK(svc.total_area() == 37);
}
void an_empty_service() {
    AreaService svc;
    CHECK(svc.count() == 0);
    CHECK(svc.total_area() == 0);
    CHECK(svc.largest() == nullptr);
}
void the_largest_is_found_and_ties_go_to_the_first() {
    AreaService svc;
    svc.add(std::make_unique<Rect>(2, 2));
    svc.add(std::make_unique<Square>(3));
    svc.add(std::make_unique<Rect>(1, 9));
    const Shape* big = svc.largest();
    CHECK(big != nullptr);
    CHECK(big->area() == 9);
    CHECK(big->name() == "square");               // the Square(3) came before Rect(1, 9)
}
void a_null_shape_is_refused() {
    AreaService svc;
    CHECK_THROWS(svc.add(nullptr));
    CHECK(svc.count() == 0);
}
void a_shape_from_the_caller_works_and_is_destroyed_with_the_service() {
    CHECK(live == 0);
    {
        AreaService svc;
        svc.add(std::make_unique<Probe>(100));
        svc.add(std::make_unique<Probe>(7));
        CHECK(live == 2);
        CHECK(svc.total_area() == 107);
        CHECK(svc.largest()->name() == "probe");
    }
    CHECK(live == 0);
}
void the_twin_gives_the_same_total() {
    struct R { long long w, h; long long area() const { return w * h; } };
    std::vector<R> t{{3, 4}, {5, 5}, {1, 1}};
    AreaService svc;
    svc.add(std::make_unique<Rect>(3, 4));
    svc.add(std::make_unique<Rect>(5, 5));
    svc.add(std::make_unique<Rect>(1, 1));
    CHECK(total_area_of(t) == svc.total_area());
    CHECK(total_area_of(t) == 38);
    CHECK(total_area_of(std::vector<R>{}) == 0);
}

int main() {
    RUN(the_shapes_answer_for_themselves);
    RUN(the_service_totals_a_mixed_list);
    RUN(an_empty_service);
    RUN(the_largest_is_found_and_ties_go_to_the_first);
    RUN(a_null_shape_is_refused);
    RUN(a_shape_from_the_caller_works_and_is_destroyed_with_the_service);
    RUN(the_twin_gives_the_same_total);
    return check::report();
}
