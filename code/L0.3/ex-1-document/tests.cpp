#include <memory>
#include <stdexcept>

#include "check.hpp"
#include "document.hpp"

void a_document_renders_its_paragraphs_with_their_fonts() {
    FontTable fonts;
    fonts.add("Serif", 12);
    fonts.add("Mono", 10);
    Document d(fonts);
    d.add_paragraph("Hello", "Serif");
    d.add_paragraph("x = 1", "Mono");
    CHECK(d.paragraph_count() == 2);
    CHECK(d.render() == "[Serif 12] Hello\n[Mono 10] x = 1\n");
}
void an_unknown_font_is_refused_and_nothing_is_added() {
    FontTable fonts;
    fonts.add("Serif", 12);
    Document d(fonts);
    CHECK_THROWS(d.add_paragraph("Hi", "Comic"));
    CHECK(d.paragraph_count() == 0);
}
void the_fonts_survive_the_document() {
    FontTable fonts;
    fonts.add("Serif", 12);
    {
        Document d(fonts);
        d.add_paragraph("Hello", "Serif");
    }
    CHECK(fonts.find("Serif") != nullptr);
    CHECK(fonts.find("Serif")->size == 12);
}
void two_documents_share_one_font_object() {
    FontTable fonts;
    fonts.add("Serif", 12);
    Document a(fonts), b(fonts);
    a.add_paragraph("A", "Serif");
    b.add_paragraph("B", "Serif");
    CHECK(a.paragraph(0).font == b.paragraph(0).font);
    CHECK(a.paragraph(0).font == fonts.find("Serif"));
}
void a_copied_document_has_its_own_paragraphs_and_the_same_fonts() {
    FontTable fonts;
    fonts.add("Serif", 12);
    Document a(fonts);
    a.add_paragraph("one", "Serif");
    Document b = a;
    b.add_paragraph("two", "Serif");
    CHECK(a.paragraph_count() == 1);
    CHECK(b.paragraph_count() == 2);
    CHECK(a.paragraph(0).font == b.paragraph(0).font);
}

int main() {
    RUN(a_document_renders_its_paragraphs_with_their_fonts);
    RUN(an_unknown_font_is_refused_and_nothing_is_added);
    RUN(the_fonts_survive_the_document);
    RUN(two_documents_share_one_font_object);
    RUN(a_copied_document_has_its_own_paragraphs_and_the_same_fonts);
    return check::report();
}
