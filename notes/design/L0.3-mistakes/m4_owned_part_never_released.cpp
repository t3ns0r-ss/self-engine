#include <cstdio>

struct Engine { char block[256]; };

class Car {
public:
    Car() : engine_(new Engine{}) {}               // MISTAKE: the car owns the engine but nothing deletes it
    void start() { std::printf("started\n"); }
private:
    Engine* engine_;
};

int main() {
    for (int i = 0; i < 3; ++i) {
        Car car;
        car.start();
    }
}
