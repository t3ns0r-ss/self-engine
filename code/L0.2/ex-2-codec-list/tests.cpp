#include "check.hpp"
#include "codec.hpp"

void the_list_decides_which_classes_run() {
    auto a = load_codecs({"upper", "reverse"});
    CHECK(run_all(a, "abc") == "CBA");
    auto b = load_codecs({"reverse"});
    CHECK(run_all(b, "abc") == "cba");
}
void the_order_in_the_list_is_the_order_of_use() {
    CHECK(run_all(load_codecs({"upper", "reverse"}), "ab") == "BA");
    CHECK(run_all(load_codecs({"reverse", "upper"}), "ab") == "BA");
    CHECK(run_all(load_codecs({}), "ab") == "ab");
}
void an_unknown_name_is_refused() {
    CHECK_THROWS(load_codecs({"upper", "rot13"}));
}
void each_codec_reports_its_name() {
    auto c = load_codecs({"upper", "reverse"});
    CHECK(c[0]->name() == "upper");
    CHECK(c[1]->name() == "reverse");
}

int main() {
    RUN(the_list_decides_which_classes_run);
    RUN(the_order_in_the_list_is_the_order_of_use);
    RUN(an_unknown_name_is_refused);
    RUN(each_codec_reports_its_name);
    return check::report();
}
