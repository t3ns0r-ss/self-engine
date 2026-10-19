// rev-2-1: a Course owns its enrolments and refers to students kept in a Registry that outlives it.
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
    Course(const Registry& registry, std::size_t capacity) : registry_(&registry), capacity_(capacity) {}
    void enrol(int student_id) {
        for (int id : enrolled_)
            if (id == student_id) throw std::logic_error("already enrolled");
        if (enrolled_.size() >= capacity_) throw std::length_error("course is full");
        enrolled_.push_back(student_id);
    }
    std::size_t size() const { return enrolled_.size(); }
    std::vector<std::string> names() const {
        std::vector<std::string> out;
        for (int id : enrolled_) out.push_back(registry_->name(id));
        return out;
    }
private:
    const Registry* registry_;
    std::size_t capacity_;
    std::vector<int> enrolled_;
};
