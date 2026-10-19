#include "check.hpp"
#include "image.hpp"

void two_widgets_share_one_image() {
    ImageCache cache;
    auto a = cache.get("logo.png");
    auto b = cache.get("logo.png");
    CHECK(a == b);                  // the same object
    CHECK(a.use_count() == 2);
    CHECK(Image::live() == 1);
}

void the_image_dies_when_the_last_owner_lets_go() {
    ImageCache cache;
    auto a = cache.get("logo.png");
    auto b = a;
    a.reset();
    CHECK(Image::live() == 1);      // b still owns it
    b.reset();
    CHECK(Image::live() == 0);      // destroyed exactly once, now
}

void the_cache_does_not_keep_images_alive() {
    ImageCache cache;
    { auto a = cache.get("a.png"); CHECK(Image::live() == 1); }
    CHECK(Image::live() == 0);
}

void a_dead_entry_is_loaded_again() {
    ImageCache cache;
    { auto a = cache.get("a.png"); }
    auto again = cache.get("a.png");
    CHECK(again != nullptr);
    CHECK(again.use_count() == 1);
    CHECK(Image::live() == 1);
}

void different_names_are_different_images() {
    ImageCache cache;
    auto a = cache.get("a.png");
    auto b = cache.get("b.png");
    CHECK(a != b);
    CHECK(Image::live() == 2);
}

struct Parent;
struct Child {
    std::weak_ptr<Parent> parent;   // weak: observing the parent does not own it
    ~Child() { ++destroyed; }
    inline static int destroyed = 0;
};
struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { ++destroyed; }
    inline static int destroyed = 0;
};
void a_weak_back_pointer_lets_a_pair_be_destroyed() {
    {
        auto p = std::make_shared<Parent>();
        p->child = std::make_shared<Child>();
        p->child->parent = p;                  // would be a cycle of owners if this were shared_ptr
        CHECK(p.use_count() == 1);             // the weak pointer is not an owner
    }
    CHECK(Parent::destroyed == 1);
    CHECK(Child::destroyed == 1);
}

int main() {
    RUN(two_widgets_share_one_image);
    RUN(the_image_dies_when_the_last_owner_lets_go);
    RUN(the_cache_does_not_keep_images_alive);
    RUN(a_dead_entry_is_loaded_again);
    RUN(different_names_are_different_images);
    RUN(a_weak_back_pointer_lets_a_pair_be_destroyed);
    return check::report();
}
