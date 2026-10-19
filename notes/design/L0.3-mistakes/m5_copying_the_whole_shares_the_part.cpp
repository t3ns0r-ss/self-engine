#include <cstdio>

struct Engine { int hours = 0; };

class Car {
public:
    Car() : engine_(new Engine{}) {}
    ~Car() { delete engine_; }                     // MISTAKE: the car owns the engine, but the default copy copies the pointer
    int hours() const { return engine_->hours; }
private:
    Engine* engine_;
};

int main() {
    Car a;
    Car b = a;                                     // two cars, one engine
    std::printf("hours = %d and %d\n", a.hours(), b.hours());
}
