// A recipe book and a meal plan.
#pragma once
#include <string>
#include <vector>

class Ingredient {
public:
    Ingredient(std::string name, int grams) : name_(std::move(name)), grams_(grams) {}
private:
    std::string name_;
    int grams_;
};
class Recipe {
public:
    void add(Ingredient i) { ingredients_.push_back(std::move(i)); }
private:
    std::string name_;
    std::vector<Ingredient> ingredients_;
};
class RecipeBook {
public:
    Recipe& add_recipe() { recipes_.emplace_back(); return recipes_.back(); }
private:
    std::vector<Recipe> recipes_;
};
class MealPlan {
public:
    void plan(const Recipe& r) { days_.push_back(&r); }
private:
    std::vector<const Recipe*> days_;
};
