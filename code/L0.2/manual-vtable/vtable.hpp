// What the compiler does for `virtual`, written by hand: every object starts with a pointer to a table of functions
// that belongs to its class. A "virtual call" reads the pointer, indexes the table and calls what it finds.
#pragma once

struct ShapeTable {
    long long (*area)(const void* self);
};

struct ManualRect {
    const ShapeTable* table;          // the hidden pointer, written out
    int w, h;
};
struct ManualSquare {
    const ShapeTable* table;
    int side;
};

inline long long rect_area(const void* self) {
    const auto* r = static_cast<const ManualRect*>(self);
    return static_cast<long long>(r->w) * r->h;
}
inline long long square_area(const void* self) {
    const auto* s = static_cast<const ManualSquare*>(self);
    return static_cast<long long>(s->side) * s->side;
}

inline const ShapeTable rect_table{&rect_area};        // one table per class, shared by all its objects
inline const ShapeTable square_table{&square_area};

inline ManualRect make_rect(int w, int h) { return {&rect_table, w, h}; }
inline ManualSquare make_square(int side) { return {&square_table, side}; }

// The caller sees only "an object that starts with a table pointer".
inline long long call_area(const void* object) {
    const ShapeTable* table = *static_cast<const ShapeTable* const*>(object);
    return table->area(object);
}
