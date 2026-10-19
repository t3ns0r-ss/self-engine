# The sequence diagram shows only the paid order. The run of a declined payment has one more call than the diagram.
UML="node $ROOT/code/shared/uml/uml_check.mjs"
cat > "$B/t.cpp" <<'CPP'
#include <cstdio>
#include "model.hpp"
int main() {
    Inventory inv; inv.stock("pen", 5); Payments pay(100); Mailer mail; Shop shop(inv, pay, mail);
    call("Test", "Shop", "place_order");
    try { shop.place_order("ann@example.com", "pen", 2, 150); } catch (const std::exception&) {}
    for (const auto& l : trace) std::printf("%s\n", l.c_str());
}
CPP
g++ -std=c++23 -I"$ROOT/code/L0.4/place-order-trace" "$B/t.cpp" -o "$B/t" && "$B/t" > "$B/declined.txt"
cat > "$B/happy.mmd" <<'MMD'
sequenceDiagram
  Test->>Shop: place_order
  Shop->>Inventory: reserve
  Shop->>Payments: charge
  Shop->>Mailer: send
MMD
echo "run of a declined payment:"; cat "$B/declined.txt"
$UML sequence "$B/happy.mmd" "$B/declined.txt"
