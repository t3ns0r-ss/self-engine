struct Report { int total = 0; };

int main() {
    Report* a = new Report{3};
    Report* b = a;                     // MISTAKE: two raw pointers, and both sides believe they own it
    delete a;
    delete b;                          // second delete of the same object
    return 0;
}
