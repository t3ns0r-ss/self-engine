#include <cstdio>

class TempFile {                       // MISTAKE: owns a FILE* but the compiler-made copy copies the pointer
public:
    explicit TempFile(const char* mode) : f_(std::tmpfile()) { (void)mode; }
    ~TempFile() { if (f_) std::fclose(f_); }
private:
    std::FILE* f_;
};

int main() {
    TempFile a("w+");
    TempFile b = a;                    // two objects, one FILE*, two fclose calls
    return 0;
}
