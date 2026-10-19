#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

class Bird {
public:
    virtual ~Bird() = default;
    virtual void fly() { std::printf("flap\n"); }  // every Bird flies, says the base
};
class Sparrow : public Bird {};
class Penguin : public Bird {
public:
    void fly() override { throw std::logic_error("penguins cannot fly"); }   // MISTAKE: breaks the base's promise
};

int main() {
    std::vector<std::unique_ptr<Bird>> flock;
    flock.push_back(std::make_unique<Sparrow>());
    flock.push_back(std::make_unique<Penguin>());
    for (auto& b : flock) b->fly();                // the loop was correct for every Bird until the Penguin arrived
    std::printf("the whole flock flew\n");
}
