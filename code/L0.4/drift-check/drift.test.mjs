// Tests of the diagram checker: a diagram that is compared with the code cannot disagree with it unnoticed.
const { checkClasses, checkSequence } = await import(process.env.UML_CHECK);
let failures = 0;
const check = (name, ok) => { if (!ok) { failures++; console.error('FAIL', name); } else console.log('ok  ', name); };
const has = (errs, text) => errs.some((e) => e.includes(text));

const HPP = `
class Mailer { public: virtual ~Mailer() = default; virtual void send(int) = 0; };
class Console : public Mailer { public: void send(int) override {} };
class Order { public: void add(int) {} private: int total_ = 0; };
class Shop {
public:
    void place() {}
private:
    std::vector<std::unique_ptr<Order>> orders_;
    Mailer& mailer_;
};`;
const DIAGRAM = `classDiagram
  Mailer <|.. Console
  Shop *-- Order
  Shop o-- Mailer
`;
check('a diagram that matches the headers passes', checkClasses(DIAGRAM, [HPP]).length === 0);
check('the other spelling of the same arrows passes', checkClasses(`classDiagram
  Console ..|> Mailer
  Order --* Shop
  Mailer --o Shop
`, [HPP]).length === 0);
check('dependencies and plain associations are not compared', checkClasses(DIAGRAM + '  Shop ..> Console\n  Order --> Mailer\n', [HPP]).length === 0);

const grown = HPP.replace('Mailer& mailer_;', 'Mailer& mailer_;\n    Order* last_;');
check('a member added in the code but not drawn is reported', has(checkClasses(DIAGRAM, [grown]), 'Shop o-- Order') || has(checkClasses(DIAGRAM, [grown]), 'Shop and Order'));
const weaker = HPP.replace('std::vector<std::unique_ptr<Order>> orders_;', 'std::vector<Order*> orders_;');
check('owner changed to a pointer in the code, diagram still says owns', has(checkClasses(DIAGRAM, [weaker]), 'headers say "Shop o-- Order"'));
check('a drawn edge that is not in the code is reported', has(checkClasses(DIAGRAM + '  Order o-- Mailer\n', [HPP]), 'not in the headers: Order o-- Mailer'));
check('a class removed from the code is reported', has(checkClasses(DIAGRAM, [HPP.replace(/class Order[^\n]*\n/, '')]), 'class Order is in the diagram but not in the headers'));
check('a class added in the code is reported', has(checkClasses(DIAGRAM, [HPP + '\nclass Audit {};']), 'class Audit is in the headers but not in the diagram'));
check('an interface with a derived class is drawn as realization, not inheritance', has(checkClasses(DIAGRAM.replace('<|..', '<|--'), [HPP]), 'headers say "Mailer <|.. Console"'));

const SEQ = `sequenceDiagram
  A->>B: one
  B->>C: two
`;
check('a sequence that matches the run passes', checkSequence(SEQ, 'A->B: one\nB->C: two\n').length === 0);
check('a call missing from the diagram is reported', has(checkSequence(SEQ, 'A->B: one\nB->C: two\nC->D: three\n'), 'call 3'));
check('calls in the wrong order are reported', has(checkSequence(SEQ, 'B->C: two\nA->B: one\n'), 'call 1'));
check('a diagram with an extra call is reported', has(checkSequence(SEQ + '  C->>D: three\n', 'A->B: one\nB->C: two\n'), 'more call'));
const ALT = `sequenceDiagram
  A->>B: one
  alt fails
    B->>A: undo
  else works
    B->>C: two
  end
`;
check('each branch of alt/else is a run the diagram allows', checkSequence(ALT, 'A->B: one\nB->A: undo\n').length === 0 && checkSequence(ALT, 'A->B: one\nB->C: two\n').length === 0);
check('a diagram with no branch cannot explain the failing run', has(checkSequence(SEQ, 'A->B: one\nB->A: undo\n'), 'call 2'));
if (failures) process.exit(1);
