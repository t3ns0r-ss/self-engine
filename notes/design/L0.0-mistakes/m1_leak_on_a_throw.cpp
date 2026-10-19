#include <stdexcept>

struct Image { char pixels[4096]; };

int parse(int n) {                     // MISTAKE: a raw new, freed by hand at the end
    Image* img = new Image();
    if (n < 0) throw std::invalid_argument("negative");   // the delete below is skipped
    img->pixels[0] = 1;
    int r = img->pixels[0] + n;
    delete img;
    return r;
}

int main() {
    try { parse(-1); } catch (const std::invalid_argument&) {}
    return parse(1) - 2;
}
