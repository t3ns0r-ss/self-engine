#include <cstdio>

class Rect {
public:
    Rect(long long w, long long h) : w_(w), h_(h) {}
    virtual ~Rect() = default;
    virtual void set_width(long long w) { w_ = w; }
    virtual void set_height(long long h) { h_ = h; }
    long long area() const { return w_ * h_; }
private:
    long long w_, h_;
};

class Square : public Rect {                       // MISTAKE: a square "is a" rectangle, but cannot keep its promises
public:
    explicit Square(long long s) : Rect(s, s) {}
    void set_width(long long w) override { Rect::set_width(w); Rect::set_height(w); }
    void set_height(long long h) override { Rect::set_width(h); Rect::set_height(h); }
};

// Written for Rect: "make it 10 wide; the height stays, so the area is 10 times the height".
long long area_when_10_wide(Rect& r, long long height) {
    r.set_height(height);
    r.set_width(10);
    return r.area();
}

int main() {
    Rect r(1, 1);
    Square s(1);
    long long a = area_when_10_wide(r, 4);
    long long b = area_when_10_wide(s, 4);
    std::printf("rect: %lld (expected 40), square: %lld (expected 40)\n", a, b);
    return a == 40 && b == 40 ? 0 : 1;
}
