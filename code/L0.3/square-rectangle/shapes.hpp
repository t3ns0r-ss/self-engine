// Inheritance needs a true is-a: a derived class must keep every promise of its base.
#pragma once

using Len = long long;

class Rect {
public:
    Rect(Len w, Len h) : w_(w), h_(h) {}
    virtual ~Rect() = default;
    virtual void set_width(Len w) { w_ = w; }
    virtual void set_height(Len h) { h_ = h; }
    Len width() const { return w_; }
    Len height() const { return h_; }
    Len area() const { return w_ * h_; }
private:
    Len w_, h_;
};

// The promise of Rect, written as a test: setting the width leaves the height alone, and the other way round.
inline bool keeps_rect_promise(Rect& r) {
    const Len h = r.height();
    r.set_width(5);
    if (r.width() != 5 || r.height() != h) return false;
    const Len w = r.width();
    r.set_height(7);
    return r.height() == 7 && r.width() == w && r.area() == w * 7;
}

// The tempting design: a square "is a" rectangle, so it derives. It cannot keep the promise above.
class BadSquare : public Rect {
public:
    explicit BadSquare(Len side) : Rect(side, side) {}
    void set_width(Len w) override { Rect::set_width(w); Rect::set_height(w); }
    void set_height(Len h) override { Rect::set_width(h); Rect::set_height(h); }
};

// The design that keeps every promise: a separate class that can still be turned into a Rect when one is needed.
class Square {
public:
    explicit Square(Len side) : side_(side) {}
    Len side() const { return side_; }
    Len area() const { return side_ * side_; }
    Square scaled(Len k) const { return Square(side_ * k); }   // a "change" builds a new Square
    Rect as_rect() const { return Rect(side_, side_); }
private:
    Len side_;
};
