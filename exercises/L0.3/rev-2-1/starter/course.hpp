// rev-2-1: a Course owns its enrolments and refers to students kept in a Registry that outlives it.
// Registry is finished. Finish Course: enrol(id) throws std::out_of_range for an id the registry does not know,
// std::logic_error if the student is already enrolled, std::length_error if the course already has `capacity`
// students; a refused call changes nothing. names() lists the students' current names in the order enrolled
// (a rename in the registry shows in the course: the course refers to students, it does not copy them).
#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

class Registry {
public:
    int add(const std::string& name) {
        names_.push_back(name);
        return static_cast<int>(names_.size()) - 1;
    }
    void rename(int id, const std::string& name) { names_.at(static_cast<std::size_t>(id)) = name; }
    const std::string& name(int id) const { return names_.at(static_cast<std::size_t>(id)); }
    bool known(int id) const { return id >= 0 && id < static_cast<int>(names_.size()); }
private:
    std::vector<std::string> names_;
};

class Course {
public:
    Course(const Registry& registry, std::size_t capacity) { (void)registry; (void)capacity; }
    void enrol(int student_id) { (void)student_id; throw std::logic_error("not implemented"); }
    std::size_t size() const { throw std::logic_error("not implemented"); }
    std::vector<std::string> names() const { throw std::logic_error("not implemented"); }
};
