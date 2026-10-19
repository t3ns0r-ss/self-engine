#include <string>
#include <vector>

#include "check.hpp"
#include "course.hpp"

void enrolled_students_are_listed_in_order() {
    Registry r;
    int ann = r.add("ann"), bo = r.add("bo"), cy = r.add("cy");
    Course c(r, 5);
    c.enrol(cy);
    c.enrol(ann);
    CHECK(c.size() == 2);
    CHECK((c.names() == std::vector<std::string>{"cy", "ann"}));
    (void)bo;
}
void a_rename_in_the_registry_shows_in_the_course() {
    Registry r;
    int ann = r.add("ann");
    Course c(r, 5);
    c.enrol(ann);
    r.rename(ann, "anna");
    CHECK((c.names() == std::vector<std::string>{"anna"}));
}
void two_courses_share_one_registry() {
    Registry r;
    int ann = r.add("ann");
    Course a(r, 5), b(r, 5);
    a.enrol(ann);
    b.enrol(ann);
    r.rename(ann, "anna");
    CHECK(a.names()[0] == "anna");
    CHECK(b.names()[0] == "anna");
}
void the_registry_survives_the_course() {
    Registry r;
    int ann = r.add("ann");
    {
        Course c(r, 5);
        c.enrol(ann);
    }
    CHECK(r.known(ann));
    CHECK(r.name(ann) == "ann");
}
void an_unknown_student_is_refused() {
    Registry r;
    r.add("ann");
    Course c(r, 5);
    CHECK_THROWS(c.enrol(7));
    CHECK_THROWS(c.enrol(-1));
    CHECK(c.size() == 0);
}
void a_student_cannot_enrol_twice() {
    Registry r;
    int ann = r.add("ann");
    Course c(r, 5);
    c.enrol(ann);
    CHECK_THROWS(c.enrol(ann));
    CHECK(c.size() == 1);
}
void a_full_course_refuses_and_changes_nothing() {
    Registry r;
    int ann = r.add("ann"), bo = r.add("bo"), cy = r.add("cy");
    Course c(r, 2);
    c.enrol(ann);
    c.enrol(bo);
    CHECK_THROWS(c.enrol(cy));
    CHECK(c.size() == 2);
    CHECK((c.names() == std::vector<std::string>{"ann", "bo"}));
}
void a_copied_course_has_its_own_enrolments() {
    Registry r;
    int ann = r.add("ann"), bo = r.add("bo");
    Course a(r, 5);
    a.enrol(ann);
    Course b = a;
    b.enrol(bo);
    CHECK(a.size() == 1);
    CHECK(b.size() == 2);
}

int main() {
    RUN(enrolled_students_are_listed_in_order);
    RUN(a_rename_in_the_registry_shows_in_the_course);
    RUN(two_courses_share_one_registry);
    RUN(the_registry_survives_the_course);
    RUN(an_unknown_student_is_refused);
    RUN(a_student_cannot_enrol_twice);
    RUN(a_full_course_refuses_and_changes_nothing);
    RUN(a_copied_course_has_its_own_enrolments);
    return check::report();
}
