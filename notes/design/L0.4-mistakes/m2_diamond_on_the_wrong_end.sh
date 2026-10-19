# The diamond is drawn at the part instead of at the whole: a reader concludes that the engine owns the car.
UML="node $ROOT/code/shared/uml/uml_check.mjs"
cat > "$B/d.mmd" <<'MMD'
classDiagram
  Engine *-- Car
MMD
$UML classes "$B/d.mmd" "$ROOT/code/L0.3/owned-engine/parts.hpp"
cat "$B/d.mmd"
