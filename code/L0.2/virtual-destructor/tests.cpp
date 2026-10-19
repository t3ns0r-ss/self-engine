#include <memory>
#include <type_traits>

#include "check.hpp"
#include "owner.hpp"

void deleting_through_the_base_runs_the_derived_destructor() {
    CHECK(live_buffers == 0);
    Handler* h = new BufferedHandler;
    CHECK(live_buffers == 1);
    delete h;                                      // defined behaviour only because ~Handler is virtual
    CHECK(live_buffers == 0);
}
void a_unique_ptr_to_the_base_cleans_up_the_derived_object() {
    {
        std::unique_ptr<Handler> h = std::make_unique<BufferedHandler>();
        CHECK(h->name() == "buffered");
        CHECK(live_buffers == 1);
    }
    CHECK(live_buffers == 0);
}
void many_objects_all_release() {
    {
        std::unique_ptr<Handler> a = std::make_unique<BufferedHandler>();
        std::unique_ptr<Handler> b = std::make_unique<BufferedHandler>();
        CHECK(live_buffers == 2);
    }
    CHECK(live_buffers == 0);
}
void the_base_destructor_is_virtual() {
    static_assert(std::has_virtual_destructor_v<Handler>);
    CHECK(std::has_virtual_destructor_v<Handler>);
}

int main() {
    RUN(deleting_through_the_base_runs_the_derived_destructor);
    RUN(a_unique_ptr_to_the_base_cleans_up_the_derived_object);
    RUN(many_objects_all_release);
    RUN(the_base_destructor_is_virtual);
    return check::report();
}
